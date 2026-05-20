//
//  splash_image.hpp
//
//  Image-sequence boot splash overlay. Reads pre-baked JPG frames from
//  romfs:/img/splash_frames/frame_NNNN.jpg (transcoded offline from a
//  source video), then plays them back at 30 fps via a worker thread
//  that fread+stb_image-decodes one frame ahead and a UI thread that
//  lazily creates a single NanoVG texture and nvgUpdateImage()s into
//  it each frame.
//
//  To customize the splash for your own build: render your video to
//  1280x720 / 30fps JPGs named frame_0001.jpg ... frame_NNNN.jpg with
//      ffmpeg -i your_video.mp4 \
//          -vf "scale=1280:720,fps=30" -q:v 5 \
//          resources/img/splash_frames/frame_%04d.jpg
//  then update kTotalFrames in splash_image.cpp to match the number
//  of files produced.
//
//  Why this instead of ffmpeg sw decode:
//    - ffmpeg's H.264 sw decoder needs thread_count=4 FF_THREAD_FRAME
//      to keep up at 1080p60. That saturates the 3 user-accessible
//      A57 cores (Switch Application mode has 0/1/2; 3 is the OS) and
//      starves Moonlight's network / mDNS / RTSP-handshake threads
//      (all normal priority 0x2c), so autoconnect's HTTPS pairing or
//      RTSP SETUP would time out before the splash finished.
//    - JPG decode at 720p with stb_image is ~15-25 ms per frame on
//      one A57 core, so a single worker thread comfortably handles
//      the 33 ms per-frame budget at 30 fps. CPU usage drops by ~4x.
//
//  Lifetime / dismissal:
//    - Plays through all kTotalFrames frames at kFps then signals
//      video_ended and the UI thread pops itself the next tick.
//    - Hard upper bound at kSafetyLifetimeMs in case something goes
//      sideways with worker scheduling (so we never live-lock).
//

#pragma once

#ifdef __SWITCH__

#include <borealis.hpp>

namespace splash {

// Returns true if at least the first frame
// (romfs:/img/splash_frames/frame_0001.jpg) can be opened. Use this
// to gate pushing SplashImageAnimActivity so a missing or empty frame
// folder is a clean no-op (no black screen, no log spam).
bool has_frames();

class SplashImageAnimActivity : public brls::Activity {
  public:
    SplashImageAnimActivity();
    brls::View* createContentView() override;
};

}  // namespace splash

#endif  // __SWITCH__
