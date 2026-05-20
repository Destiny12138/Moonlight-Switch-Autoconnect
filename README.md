<p align="right">
  <b>English</b> &nbsp;|&nbsp; <a href="README.zh-CN.md">简体中文</a>
</p>

# Moonlight-Switch-Autoconnect

A friendly fork of [XITRIX/Moonlight-Switch](https://github.com/XITRIX/Moonlight-Switch) that adds two opt-in features on top of the upstream Switch port of the [Moonlight Game Streaming Project](https://github.com/moonlight-stream):

- **[Auto-connect](#auto-connect)** — start streaming immediately on launch by adding a small block to `settings.json`. No code or UI changes needed.
- **[Splash animation](#splash-animation)** — play your own pre-rendered animated boot intro on top of the main UI, with cheap CPU usage so it never blocks Moonlight's network setup.

Everything else is the upstream behavior. When neither feature is configured, this fork behaves exactly like upstream. Jump to the [feature details](#auto-connect) at the bottom of this page for setup instructions.

> The build pipeline, controls, NSP forwarder, localization and platform support are unchanged from upstream — see the sections below for those.

## Screenshots
<details>
  <summary>Preview</summary>
  <p float="left">
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712658-20382345-2da5-4968-9f57-f9f4470ae819.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712664-bf2481b2-2791-490d-99a9-2f968682db76.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712669-fd8b2495-e1ea-4357-949f-7fa7312da46f.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712672-b9ac3785-bd1c-4948-82b2-9b353019feba.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712676-aaa85bb7-9517-4a6d-bc35-070df092383c.jpg" />
  </p>
</details>

# Installing
### Switch
1. Download latest Moonlight-Switch [release](https://github.com/XITRIX/Moonlight-Switch/releases).
2. Put Moonlight.nro to sdcard:/switch/Moonlight-Switch;
3. Launch hbmenu over *Title Redirection* (for FULL RAM access);
4. Launch moonlight.

Or download it from [HB App Store](https://apps.fortheusers.org/switch/Moonlight-Switch)

> [!TIP]
> To be able to use high bitrate setting especially with 1080p - resolution, you need to overclock CPU/GPU of your console.
>
> To learn more about that you can take a look at [Sys-Clk homebrew](https://github.com/retronx-team/sys-clk) or entire [Atmosphere build - 4IFIR](https://github.com/rashevskyv/4IFIR/blob/main/README_ENG.md) which includes everything you need to overclock your console

> [!WARNING]
> I DO NOT RESPOSIBLE FOR ANY DAMAGE TO YOUR CONSOLE IF SOMETHING WILL GO WRONG!
>
> I am using 4IFIR by myself and not find any issue, but everything is possible. So think by you own head and be responsible for what you do with your devices!

### iOS, tvOS and macOS
Accept [invite for TestFlight](https://testflight.apple.com/join/P9EX5vQ5) and download app from there

## Discord
Feel free to join [Moonlight discord server](https://discord.gg/fmtcVPzaG4), you will find me there in "switch-help" channel 

## Controls
### Mouse
With touch screen you can move your coursor, tap to left click, scroll 2 fingers to scroll.

While touching screen ZR and ZL buttons will work like left and right mouse buttons.

Also while touching screen L and R sticks will work like scrolling wheel.

USB mouse working as well.

### Keyboard
You can use onscreen keyboard, tap 3 fingers on screen to show it.

USB keyboard working as well.

### Gamepad
By default, Switch gamepad configured as X360 gamepad (A/B and X/Y swapped). Key mapping available in application settings.

Up to 5 gamepads (includes handheld mode) supported. Half of joycons are also supported.

### SixAxis
You should configure your Sunshine server to recognise controller as DS4 one to be able to use Gyro and Accelerometer. Only works for player 1 controller.

### Ingame overlay
To open overlay, press - and + key simultaneously by default or Hold ESC on keyboard.

Key combination and holding time are configurable in settings.

## NSP forwarder
App supports NSP forwarders to start stream immediately with predefined configuration. Add app you want to launch in Favorites list first. You can generate forwarder using [NSP Forwarder Generator](https://nsp-forwarder.vercel.app/moonlight)

### Manually
If you'd like to create it manually, without help of generator, you'll need to create forwarder which will pass thees arguments to the application:
- `--ip` - IP address of your PC
- `--appid` - ID of the app to launch, it has to be added into "Favorites list" (you could find it in /switch/Moonlight-Switch/settings.json)
- `--appname` - The name of the app without any spacings

example:
`--ip=192.168.1.101 --appid=1233211234 --appname=Steam`

## Localization
- English (100%)
- Russian (100%)
- German (86%)
- Spanish (72%)
- Japanese (70%)
- Chinese (simplified) (86%)
- Czech (70%) - unsupported yet, as HOS has no such system language

### Contribution
If you'd like to improve existing language, or add a new one, follow the instruction:
1. Ask a permission to modify language [here](https://poeditor.com/join/project?hash=9kiCIvN0dc)
2. Notify me by [creating an issue](https://github.com/XITRIX/Moonlight-Switch/issues/new) with title "[Localization] - {Name of language}", in description write your nickname on POEditor
3. After translation is done, notify me in issue created earlier

You have 2 options to add that translation:
1. If you'd like your profile in "contributors" section, you could add that localization by creating a PR
2. If you don't care, I could do that by myself

If you'd like to test your translation, you could follow build instructions, or ask me to create a build with your localization, I'll attach that build in issue.

> [!WARNING]
> Currently there is no way to select language inside of app, it takes from system settings, so it is impossible to add locatization, that HOS doesn't support (that happend with Czech language).

## Build Moonlight-Switch

```bash
cd 'folder/to/store/the/sources'

# Clone this repo with submodules
git clone https://github.com/Destiny12138/Moonlight-Switch-Autoconnect.git --recursive
cd Moonlight-Switch-Autoconnect
```

### Switch

To build for Switch, a standard development environment must first be set up. In order to do so, [refer to the Getting Started guide](https://devkitpro.org/wiki/Getting_Started).

```bash
cmake -B build/switch -DPLATFORM_SWITCH=ON
make -C build/switch Moonlight.nro -j$(nproc)
```

### PC (Windows/Linux/MacOS)

To build for PC, the following components are required:

- cmake/make build system
- A C++ compiler supporting the C++17 standard

Please refer to the usual sources of information for your particular operating system. Usually the commands needed to build this project will look like this:

```bash
cmake -B build/pc -DPLATFORM_DESKTOP=ON -DCMAKE_BUILD_TYPE=Release
make -C build/pc -j$(nproc)
```

Also, please note that the `resources` folder must be available in the working directory, otherwise the program will fail to find the shaders.

#### Windows (MSYS2)

Windows desktop builds are supported through MSYS2 system packages for both x64 and ARM64.

MSYS2 is recommended under `C:\msys64`.

##### x64 (UCRT64)

Install the required packages:

```bash
pacman -S --needed --noconfirm \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja \
  mingw-w64-ucrt-x86_64-pkgconf \
  mingw-w64-ucrt-x86_64-SDL2 \
  mingw-w64-ucrt-x86_64-ffmpeg \
  mingw-w64-ucrt-x86_64-curl \
  mingw-w64-ucrt-x86_64-mbedtls \
  mingw-w64-ucrt-x86_64-jansson \
  mingw-w64-ucrt-x86_64-libpng \
  mingw-w64-ucrt-x86_64-opus \
  mingw-w64-ucrt-x86_64-expat \
  mingw-w64-ucrt-x86_64-zstd
```

Build with the bundled preset:

These Windows presets default to native D3D11 (DirectX 11). Pass `-DUSE_D3D11=OFF` when configuring only if you want to force the legacy OpenGL path.

```bash
cmake --preset windows-ucrt64-release
cmake --build --preset windows-ucrt64-release
```

The resulting executable is placed in `build/windows-ucrt64`. The build stages the required MSYS2 UCRT64 DLLs beside `Moonlight.exe`; keep the generated `resources` directory there as well, because the UCRT64 build uses external resources instead of `libromfs`.

##### ARM64 (CLANGARM64)

To build a native Windows ARM64 executable, install the CLANGARM64 packages:

```bash
pacman -S --needed --noconfirm \
  mingw-w64-clang-aarch64-clang \
  mingw-w64-clang-aarch64-cmake \
  mingw-w64-clang-aarch64-ninja \
  mingw-w64-clang-aarch64-pkgconf \
  mingw-w64-clang-aarch64-SDL2 \
  mingw-w64-clang-aarch64-ffmpeg \
  mingw-w64-clang-aarch64-curl \
  mingw-w64-clang-aarch64-mbedtls \
  mingw-w64-clang-aarch64-jansson \
  mingw-w64-clang-aarch64-libpng \
  mingw-w64-clang-aarch64-opus \
  mingw-w64-clang-aarch64-expat \
  mingw-w64-clang-aarch64-zstd
```

Build with the ARM64 preset:

```bash
cmake --preset windows-clangarm64-release
cmake --build --preset windows-clangarm64-release
```

The resulting executable is placed in `build/windows-clangarm64`. The build stages the required MSYS2 CLANGARM64 DLLs beside `Moonlight.exe`; keep the generated `resources` directory there as well, because the desktop ARM64 build also uses external resources instead of `libromfs`.

### iOS / tvOS:

```shell
# build libromfs generator
./build_libromfs_generator.sh

# prepare vcpkg
./extern/vcpkg/bootstrap-vcpkg.sh
```

#### 1. Build for arm64 iphoneOS

```shell
# 1. Generate a Xcode project
cmake -B build/ios -G Xcode -DPLATFORM_IOS=ON

# 2. open project in Xcode
open build/ios/*.xcodeproj

# 3. Set up Team and Bundle Identifiers in Xcode, then connect devices to run.
```

#### 2. Build for arm64 tvOS

```shell
# 1. Generate a Xcode project
cmake -B build/tvos -G Xcode -DPLATFORM_TVOS=ON

# 2. open project in Xcode
open build/tvos/*.xcodeproj

# 3. Set up Team and Bundle Identifiers in Xcode, then connect devices to run.
```

---

# Feature details

The two opt-in features this fork adds over upstream. Skip these sections if you only want the standard upstream behavior.

## Auto-connect

Skip the manual click-through (host list → game list → stream) when you always launch Moonlight to play the same PC + game. If a valid `autoconnect` block is found in `settings.json`, `StreamingView` is pushed on top of `MainActivity` on launch and the stream starts straight away. Disconnect / exit drops you back to the normal UI, exactly as if you had dismissed a stream by hand.

### Setup

1. Pair your host and add at least one favorite once, through the normal UI.
2. Open `sdmc:/switch/Moonlight-Switch/settings.json` and add an `autoconnect` block at the top level:

   ```json
   {
     "hosts": [ ... ],
     "settings": { ... },
     "autoconnect": {
       "host": "192.168.1.10",
       "app_id": 1234567890
     }
   }
   ```

   | Field    | Type   | Required | Description |
   | -------- | ------ | -------- | ----------- |
   | `host`   | string | one of `host`/`mac` | The host's `address` or `remote_address` from the matching `hosts[]` entry. |
   | `mac`    | string | one of `host`/`mac` | The host's `mac` from the matching `hosts[]` entry. Useful when the LAN address can change. |
   | `app_id` | int    | yes | The `id` of one of that host's `favorites[]` entries. |

3. Launch Moonlight. If the host **and** the favorite both resolve, streaming starts immediately. If either does not, Moonlight silently falls through to the normal main menu.

### Disable

Delete the `autoconnect` block from `settings.json`. The block is round-tripped on save (so unrelated UI changes — adding a host, toggling a setting — do not wipe it out), but removing it by hand will.

### Caveats

- Auto-connect targets one specific favorite; it does not discover or pair hosts.
- Make sure the host and favorite resolve before relying on it — a typo in `app_id` just drops you back to the main menu.

## Splash animation

Adds an optional animated boot splash that plays on top of the main UI on Switch startup. Frames are pre-rendered offline to JPGs so playback is cheap (~one CPU core via `stb_image`) and does not steal threads from Moonlight's network / pairing / RTSP setup happening in parallel. Press any controller button to skip.

### Setup

1. Render your source video into `resources/img/splash_frames/`:

   ```bash
   ffmpeg -i your_video.mp4 \
       -vf "scale=1280:720,fps=30" -q:v 5 \
       resources/img/splash_frames/frame_%04d.jpg
   ```

   Frames must be named `frame_0001.jpg`, `frame_0002.jpg`, ... (4-digit, 1-based). 1280×720 / 30 fps is what the player expects.

2. Update `kTotalFrames` in [app/src/splash_image.cpp](app/src/splash_image.cpp) to match the number of files produced. The player is tolerant of small mismatches (it bails after a few consecutive misses), but a correct value avoids the 32 s safety-timer fallback.

3. Rebuild the `.nro` and reinstall.

### Disable

Leave `resources/img/splash_frames/` empty. The splash is skipped at runtime if `frame_0001.jpg` is missing, so there is no black gap on launch.

### How it works

- A single worker thread `fread`+`stbi_load_from_memory`-decodes one frame ahead.
- The UI thread does one `nvgUpdateImage` per frame and paints a letterbox-fit pattern.
- Drains when the worker finishes OR a 32 s safety timer trips, then `popActivity(NONE)` reveals the UI underneath.
- Frame files are **not** committed to the repo — the top-level `.gitignore` ignores `resources/img/splash_frames/*` and only `.gitkeep` is tracked, so the folder stays in tree but you supply your own assets.

### Why JPGs and not a video file

`ffmpeg`'s H.264 software decoder needs 4 frame threads to keep up at 1080p, which saturates the 3 user-accessible A57 cores on Switch and starves Moonlight's network workers. JPG decode at 720p with `stb_image` takes ~15–25 ms per frame on one core, which fits comfortably in the 33 ms / frame budget at 30 fps and leaves the other two cores free for mDNS / HTTPS pairing / RTSP setup to run in parallel with the splash.

---

## Credits

Upstream Moonlight-Switch by [XITRIX](https://github.com/XITRIX). This fork only adds the two opt-in features described above; all rendering, streaming, controls and platform support are upstream's work.

Thanks a lot to [Rock88](https://github.com/rock88) and his [Moonlight-NX](https://github.com/rock88/moonlight-nx), lots of streaming code has been lend from it 👍.

[Xfangfang](https://github.com/xfangfang) for maintaining [Borealis](https://github.com/xfangfang/borealis) library. iOS port would not be possible without it. 

[Averne](https://github.com/averne) for NVDEC implementation into [FFmpeg](https://github.com/averne/FFmpeg) and useful guidance of how to enable it 

Also huge thanks to [Cooler3D](https://github.com/Cooler3Ds) for help with Deko3D implementation and solving performance issues
