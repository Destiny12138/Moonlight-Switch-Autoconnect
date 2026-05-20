//
//  splash_image.cpp
//
//  See splash_image.hpp for the rationale.
//

#ifdef __SWITCH__

#include "splash_image.hpp"

#include <switch.h>

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

namespace splash {

namespace {

// === Sequence parameters ===========================================
// These MUST match the ffmpeg transcode that wrote
// resources/img/splash_frames/frame_NNNN.jpg:
//   ffmpeg -i your_video.mp4 \
//       -vf "scale=1280:720,fps=30" -q:v 5 \
//       resources/img/splash_frames/frame_%04d.jpg
constexpr int      kCanvasW            = 1280;
constexpr int      kCanvasH            = 720;
constexpr int      kFps                = 30;
constexpr int      kTotalFrames        = 889;
constexpr uint64_t kSafetyLifetimeMs   = 32000;     // > kTotalFrames / kFps s
constexpr size_t   kRgbaSize           = (size_t)kCanvasW * kCanvasH * 4;

constexpr const char* kFrameDir = "romfs:/img/splash_frames";

// We don't pull in stb_image.h to avoid header-include-order pain;
// nanovg.c already defines STB_IMAGE_IMPLEMENTATION so these symbols
// are linked into the .nro. We just forward-declare the two we need.
extern "C" {
unsigned char* stbi_load_from_memory(const unsigned char* buffer, int len,
                                     int* x, int* y, int* channels_in_file,
                                     int desired_channels);
void           stbi_image_free(void* retval_from_stbi_load);
}

}  // namespace

bool has_frames() {
    // Probe the first frame only. If the folder is missing entirely,
    // fopen returns null. If it exists but is empty, the file is also
    // absent and fopen returns null. Either way, fall through to "no
    // splash" so the caller can skip pushing the activity.
    char path[128];
    std::snprintf(path, sizeof(path), "%s/frame_0001.jpg", kFrameDir);
    FILE* fp = std::fopen(path, "rb");
    if (!fp) return false;
    std::fclose(fp);
    return true;
}

namespace {

class SplashImageAnimView : public brls::Box {
  public:
    SplashImageAnimView() {
        // Solid black background — no bleed-through from MainActivity.
        setBackgroundColor(nvgRGBA(0, 0, 0, 0xFF));
        setGrow(1.0f);
        setWidth(brls::View::AUTO);
        setHeight(brls::View::AUTO);

        ui_buf.resize(kRgbaSize, 0);
        consume_buf.resize(kRgbaSize, 0);

        worker = std::thread(&SplashImageAnimView::worker_main, this);
    }

    ~SplashImageAnimView() override {
        stop_requested.store(true, std::memory_order_release);
        if (worker.joinable()) worker.join();
        if (nvg_image >= 0) {
            NVGcontext* vg = brls::Application::getNVGContext();
            if (vg) nvgDeleteImage(vg, nvg_image);
            nvg_image = -1;
        }
    }

    void draw(NVGcontext* vg, float x, float y, float w, float h,
              brls::Style style, brls::FrameContext* ctx) override {
        // Base box (paints black background).
        brls::Box::draw(vg, x, y, w, h, style, ctx);

        if (start_tick == 0) {
            start_tick = armGetSystemTick();
        }

        // Consume one frame from the worker if available.
        bool have_new = frame_ready.exchange(false, std::memory_order_acquire);
        if (have_new) {
            std::lock_guard<std::mutex> lk(frame_mtx);
            std::swap(consume_buf, ui_buf);
            ui_frame_index = produced_index;
        }

        // Allow skipping the splash with any button press, but only on the
        // transition from no buttons pressed to at least one button pressed.
        bool any_button_pressed = false;
        const auto& controller_state = brls::Application::getControllerState();
        for (bool pressed : controller_state.buttons) {
            if (pressed) {
                any_button_pressed = true;
                break;
            }
        }
        if (!skip_button_latched && any_button_pressed) {
            skip_button_latched = true;
            dismissed = true;
            brls::sync([]() {
                brls::Application::popActivity(
                    brls::TransitionAnimation::NONE);
            });
        } else if (!any_button_pressed) {
            skip_button_latched = false;
        }

        // Lazy texture create on the first real frame (avoids a black
        // flash of an empty texture). Subsequent frames just update.
        if (nvg_image < 0) {
            if (have_new) {
                nvg_image = nvgCreateImageRGBA(
                    vg, kCanvasW, kCanvasH,
                    NVG_IMAGE_NEAREST, consume_buf.data());
            }
        } else if (have_new) {
            nvgUpdateImage(vg, nvg_image, consume_buf.data());
        }

        // Paint full-screen with FIT (preserve aspect, letterbox black).
        if (nvg_image >= 0) {
            const float ca = (float)kCanvasW / (float)kCanvasH;
            const float va = w / h;
            float dw, dh, dx, dy;
            if (va > ca) {
                dh = h;
                dw = h * ca;
                dx = x + (w - dw) * 0.5f;
                dy = y;
            } else {
                dw = w;
                dh = w / ca;
                dx = x;
                dy = y + (h - dh) * 0.5f;
            }
            NVGpaint paint =
                nvgImagePattern(vg, dx, dy, dw, dh, 0.0f, nvg_image, 1.0f);
            nvgBeginPath(vg);
            nvgRect(vg, dx, dy, dw, dh);
            nvgFillPaint(vg, paint);
            nvgFill(vg);
        }

        uint64_t now        = armGetSystemTick();
        uint64_t elapsed_ms = armTicksToNs(now - start_tick) / 1000000ULL;

        // Dismissal:
        //   - drained: worker ended and UI has consumed every frame the
        //     worker actually produced (works whether kTotalFrames was
        //     accurate, too high, or too low — we trust produced_index
        //     instead of the constant)
        //   - safety: hard upper bound in case anything live-locks
        bool ended   = video_ended.load(std::memory_order_acquire);
        bool drained = ended && (ui_frame_index >= produced_index.load());
        if ((drained || elapsed_ms >= kSafetyLifetimeMs) && !dismissed) {
            dismissed = true;
            brls::sync([]() {
                brls::Application::popActivity(
                    brls::TransitionAnimation::NONE);
            });
        }
    }

  private:
    void worker_main() {
        std::vector<uint8_t> worker_buf(kRgbaSize, 0);
        std::vector<uint8_t> file_buf;
        file_buf.reserve(128 * 1024);  // typical 720p JPG fits

        const uint64_t start = armGetSystemTick();

        // If kTotalFrames was set higher than the actual on-disk frame
        // count (e.g. user dropped in a shorter sequence and forgot to
        // update kTotalFrames), this lets us bail out early instead of
        // sleeping all the way to the PTS of the last phantom frame.
        constexpr int kMaxConsecutiveMisses = 5;
        int consecutive_misses = 0;

        for (int i = 1;
             i <= kTotalFrames &&
             !stop_requested.load(std::memory_order_acquire);
             ++i) {
            // PTS pacing: target = i / kFps seconds from start.
            int64_t target_ms = (int64_t)i * 1000 / kFps;
            int64_t now_ms    =
                (int64_t)(armTicksToNs(armGetSystemTick() - start) /
                          1000000ULL);
            int64_t delta = target_ms - now_ms;
            if (delta > 5) {
                svcSleepThread((uint64_t)(delta - 2) * 1000000ULL);
            }

            // Load JPG.
            char path[128];
            std::snprintf(path, sizeof(path), "%s/frame_%04d.jpg",
                          kFrameDir, i);
            FILE* fp = std::fopen(path, "rb");
            if (!fp) {
                if (++consecutive_misses >= kMaxConsecutiveMisses) break;
                continue;
            }
            consecutive_misses = 0;
            std::fseek(fp, 0, SEEK_END);
            long sz = std::ftell(fp);
            std::fseek(fp, 0, SEEK_SET);
            if (sz <= 0) {
                std::fclose(fp);
                continue;
            }
            file_buf.resize((size_t)sz);
            size_t n = std::fread(file_buf.data(), 1, (size_t)sz, fp);
            std::fclose(fp);
            if (n != (size_t)sz) continue;

            int            w = 0, h = 0, ch = 0;
            unsigned char* px = stbi_load_from_memory(
                file_buf.data(), (int)sz, &w, &h, &ch, 4);
            if (!px) {
                continue;
            }

            if (w == kCanvasW && h == kCanvasH) {
                std::memcpy(worker_buf.data(), px, kRgbaSize);
            } else {
                // Wrong dim — shouldn't happen with our preset, but
                // black-fill so we don't show garbage.
                std::memset(worker_buf.data(), 0, kRgbaSize);
            }
            stbi_image_free(px);

            // Hand off to UI thread.
            {
                std::lock_guard<std::mutex> lk(frame_mtx);
                std::swap(worker_buf, ui_buf);
                produced_index.store(i, std::memory_order_release);
            }
            frame_ready.store(true, std::memory_order_release);
        }

        video_ended.store(true, std::memory_order_release);
    }

    // UI thread state.
    int      nvg_image      = -1;
    uint64_t start_tick     = 0;
    bool     dismissed      = false;
    bool     skip_button_latched = false;
    int      ui_frame_index = 0;

    // Worker / shared state.
    std::thread             worker;
    std::mutex              frame_mtx;
    std::vector<uint8_t>    ui_buf;       // produced by worker, consumed by UI
    std::vector<uint8_t>    consume_buf;  // UI thread only, fed to nvgUpdateImage
    std::atomic<bool>       frame_ready{false};
    std::atomic<bool>       stop_requested{false};
    std::atomic<bool>       video_ended{false};
    std::atomic<int>        produced_index{0};
};

}  // namespace

SplashImageAnimActivity::SplashImageAnimActivity() {}

brls::View* SplashImageAnimActivity::createContentView() {
    auto* v = new SplashImageAnimView();
    v->setDimensions(brls::View::AUTO, brls::View::AUTO);
    v->setGrow(1.0f);
    return v;
}

}  // namespace splash

#endif  // __SWITCH__
