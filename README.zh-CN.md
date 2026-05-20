<p align="right">
  <a href="README.md">English</a> &nbsp;|&nbsp; <b>简体中文</b>
</p>

# Moonlight-Switch-Autoconnect

[XITRIX/Moonlight-Switch](https://github.com/XITRIX/Moonlight-Switch) 的友好 fork，在上游 Switch 版 [Moonlight Game Streaming Project](https://github.com/moonlight-stream) 的基础上新增两个可选特性：

- **[自动连接 Auto-connect](#自动连接-auto-connect)** — 在 `settings.json` 中加一段配置即可在启动时直接进入串流，无需任何代码或界面改动。
- **[启动动画 Splash animation](#启动动画-splash-animation)** — 启动时在主界面之上播放你自己预渲染的动画作为开场，CPU 占用极低，不会阻塞 Moonlight 的网络握手。

其余行为与上游完全一致；当两个特性都未配置时，本 fork 的运行表现与上游一模一样。跳到页面底部的 [特性详解](#特性详解) 查看详细配置步骤。

> 构建流程、操控、NSP forwarder、本地化与各平台支持均与上游保持一致，详见下方对应章节。

## 截图

<details>
  <summary>预览</summary>
  <p float="left">
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712658-20382345-2da5-4968-9f57-f9f4470ae819.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712664-bf2481b2-2791-490d-99a9-2f968682db76.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712669-fd8b2495-e1ea-4357-949f-7fa7312da46f.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712672-b9ac3785-bd1c-4948-82b2-9b353019feba.jpg" />
  <img width="500" src="https://user-images.githubusercontent.com/9553519/135712676-aaa85bb7-9517-4a6d-bc35-070df092383c.jpg" />
  </p>
</details>

# 安装

### Switch

1. 下载最新的 Moonlight-Switch [release](https://github.com/XITRIX/Moonlight-Switch/releases)。
2. 将 `Moonlight.nro` 放到 `sdcard:/switch/Moonlight-Switch`。
3. 通过 *Title Redirection* 启动 hbmenu（以获得完整 RAM 访问权限）。
4. 启动 Moonlight。

也可以通过 [HB App Store](https://apps.fortheusers.org/switch/Moonlight-Switch) 下载。

> [!TIP]
> 想要在 1080p 等高分辨率下使用高码率，需要给主机超频 CPU/GPU。
>
> 可参考 [Sys-Clk homebrew](https://github.com/retronx-team/sys-clk) 或 [Atmosphere build - 4IFIR](https://github.com/rashevskyv/4IFIR/blob/main/README_ENG.md)，后者已经把超频所需的一切打包齐全。

> [!WARNING]
> 操作不当对主机造成的任何损坏，作者概不负责！
>
> 作者本人长期在用 4IFIR 未遇问题，但凡事皆有可能。请在了解风险后自行决定，并对自己的设备负责。

### iOS、tvOS 与 macOS

接受 [TestFlight 邀请](https://testflight.apple.com/join/P9EX5vQ5)，在里面下载即可。

## Discord

欢迎加入 [Moonlight discord 服务器](https://discord.gg/fmtcVPzaG4)，可以在 "switch-help" 频道找到作者。

## 操控

### 鼠标

触摸屏可移动光标，点击为左键，双指滚动为滚轮。

触摸屏幕时，ZR/ZL 表现为左右键。

触摸屏幕时，L/R 摇杆也表现为滚轮。

支持 USB 鼠标。

### 键盘

三指点击屏幕可呼出屏幕键盘。

支持 USB 键盘。

### 手柄

Switch 手柄默认按 X360 布局映射（A/B、X/Y 互换）。在应用设置中可自定义键位。

支持最多 5 个手柄（含掌机模式）。半边 joycon 也可使用。

### SixAxis

需要把 Sunshine 服务端配置为识别为 DS4 控制器，才能使用陀螺仪与加速度计。仅对玩家 1 生效。

### 游戏内悬浮菜单

默认同时按 - 和 + 唤起；键盘上长按 ESC 也可。

组合键和长按时间均可在设置中调整。

## NSP forwarder

支持以 NSP forwarder 形式直接以预设配置启动串流。先在收藏中加入要启动的游戏，然后可用 [NSP Forwarder Generator](https://nsp-forwarder.vercel.app/moonlight) 生成。

### 手动创建

不想用生成器时，自己创建一个 forwarder 并向应用传入以下参数：

- `--ip` —— PC 的 IP 地址
- `--appid` —— 要启动的游戏 ID（需先在"收藏"中添加；可在 `/switch/Moonlight-Switch/settings.json` 中找到）
- `--appname` —— 游戏名称（不能含空格）

示例：

`--ip=192.168.1.101 --appid=1233211234 --appname=Steam`

## 本地化

- 英文（100%）
- 俄文（100%）
- 德文（86%）
- 西班牙文（72%）
- 日文（70%）
- 简体中文（86%）
- 捷克文（70%）—— 暂未启用，HOS 不支持该系统语言

### 贡献翻译

想改进现有翻译或新增语言，请按以下步骤：

1. 在 [POEditor 项目](https://poeditor.com/join/project?hash=9kiCIvN0dc) 申请权限。
2. 在上游仓库 [创建 issue](https://github.com/XITRIX/Moonlight-Switch/issues/new)，标题写 "[Localization] - {语言名}"，正文写你在 POEditor 上的昵称。
3. 翻译完成后在该 issue 中告知作者。

有两种合入方式：

1. 想把自己列入 "contributors"，可自行提交 PR。
2. 不在意的话，作者代为处理。

想测试翻译效果，可以按下文构建流程自行编译，或在 issue 中请求作者帮你出一个含你翻译的版本。

> [!WARNING]
> 目前不支持在应用内切换语言，会跟随系统语言；HOS 不支持的语言无法添加（如捷克语）。

## 构建 Moonlight-Switch-Autoconnect

```bash
cd 'folder/to/store/the/sources'

# 拉子模块一起 clone
git clone https://github.com/Destiny12138/Moonlight-Switch-Autoconnect.git --recursive
cd Moonlight-Switch-Autoconnect
```

### Switch

需要先按 [devkitPro Getting Started](https://devkitpro.org/wiki/Getting_Started) 配置好工具链。

```bash
cmake -B build/switch -DPLATFORM_SWITCH=ON
make -C build/switch Moonlight.nro -j$(nproc)
```

### PC（Windows / Linux / macOS）

需要：

- cmake / make 构建系统
- 支持 C++17 的 C++ 编译器

各系统的常规做法基本如下：

```bash
cmake -B build/pc -DPLATFORM_DESKTOP=ON -DCMAKE_BUILD_TYPE=Release
make -C build/pc -j$(nproc)
```

另外请注意，运行目录下必须有 `resources` 文件夹，否则程序找不到 shader 会启动失败。

#### Windows (MSYS2)

通过 MSYS2 系统包支持 Windows 桌面构建，x64 与 ARM64 均可。

推荐把 MSYS2 安装到 `C:\msys64`。

##### x64 (UCRT64)

安装依赖：

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

用预设构建（默认使用原生 D3D11；如需回退 OpenGL 路径，配置时加 `-DUSE_D3D11=OFF`）：

```bash
cmake --preset windows-ucrt64-release
cmake --build --preset windows-ucrt64-release
```

产物在 `build/windows-ucrt64` 下。构建过程会把 UCRT64 的 DLL 复制到 `Moonlight.exe` 旁边；同时请保留生成的 `resources` 目录，因为 UCRT64 构建使用外部资源而非 `libromfs`。

##### ARM64 (CLANGARM64)

构建原生 Windows ARM64 可执行文件，需要安装 CLANGARM64 包：

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

```bash
cmake --preset windows-clangarm64-release
cmake --build --preset windows-clangarm64-release
```

产物在 `build/windows-clangarm64` 下，注意事项同上。

### iOS / tvOS

```shell
# 先编译 libromfs 生成器
./build_libromfs_generator.sh

# 准备 vcpkg
./extern/vcpkg/bootstrap-vcpkg.sh
```

#### 1. arm64 iphoneOS

```shell
cmake -B build/ios -G Xcode -DPLATFORM_IOS=ON
open build/ios/*.xcodeproj
# 在 Xcode 里配好 Team 和 Bundle Identifier，连真机即可运行。
```

#### 2. arm64 tvOS

```shell
cmake -B build/tvos -G Xcode -DPLATFORM_TVOS=ON
open build/tvos/*.xcodeproj
# 在 Xcode 里配好 Team 和 Bundle Identifier，连真机即可运行。
```

---

# 特性详解

本 fork 在上游基础上新增的两个可选特性。只想使用上游默认行为的话可以跳过本节。

## 自动连接 Auto-connect

如果你每次启动 Moonlight 都只是为了串流同一台 PC 的同一个游戏，那么“主机列表 → 游戏列表 → 串流”的手动点击其实是可以省掉的。当 `settings.json` 中存在合法的 `autoconnect` 配置时，启动时会把 `StreamingView` 推到 `MainActivity` 之上，直接进入串流。断开或退出串流后会回落到正常的主界面，效果与你手动结束一次串流完全一致。

### 配置步骤

1. 先在正常界面里完成一次配对，并把要直连的游戏加入收藏。
2. 打开 `sdmc:/switch/Moonlight-Switch/settings.json`，在顶层加入一个 `autoconnect` 块：

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

   | 字段     | 类型   | 必填 | 说明 |
   | -------- | ------ | ---- | ---- |
   | `host`   | string | `host`/`mac` 二选一 | 对应 `hosts[]` 条目中的 `address` 或 `remote_address`。 |
   | `mac`    | string | `host`/`mac` 二选一 | 对应 `hosts[]` 条目中的 `mac`。IP 经常变动时建议用 mac 匹配。 |
   | `app_id` | int    | 是 | 该主机 `favorites[]` 中某个条目的 `id`。 |

3. 启动 Moonlight。如果主机和收藏的游戏都能被解析，则立即开始串流；只要其中任一项匹配失败，就静默回落到主界面。

### 关闭方式

把 `settings.json` 中的 `autoconnect` 块删掉即可。该块在保存时会被原样写回（因此添加主机、修改设置等无关操作不会把它抹掉），但手动删除会真正生效。

### 注意事项

- 自动连接只针对**一个**指定的收藏游戏，不会做主机发现或配对。
- 在依赖它之前请先确认主机和收藏都能被解析 —— `app_id` 写错时只是回落到主界面而已。

## 启动动画 Splash animation

在 Switch 启动时，于主界面之上播放一段可选的动画作为开场。所有帧都是离线预渲染好的 JPG，因此回放成本很低（约一个 CPU 核心，由 `stb_image` 解码），不会和 Moonlight 同时进行的网络 / 配对 / RTSP 建立抢占线程。按手柄任意按键即可跳过。

### 配置步骤

1. 用 ffmpeg 把你的源视频转码成 `resources/img/splash_frames/` 下的图片帧：

   ```bash
   ffmpeg -i your_video.mp4 \
       -vf "scale=1280:720,fps=30" -q:v 5 \
       resources/img/splash_frames/frame_%04d.jpg
   ```

   帧文件名必须为 `frame_0001.jpg`、`frame_0002.jpg`……（4 位数字、从 1 开始）。播放器期望的是 1280×720 / 30 fps。

2. 把 [app/src/splash_image.cpp](app/src/splash_image.cpp) 中的 `kTotalFrames` 改成实际生成的帧数。播放器对小幅偏差有容忍（连续若干帧读取失败就会提前结束），但准确值能避免触发 32 秒的兜底定时器。

3. 重新编译 `.nro` 并安装。

### 关闭方式

把 `resources/img/splash_frames/` 留空即可。运行时若 `frame_0001.jpg` 不存在，启动动画会被跳过，启动过程不会出现黑屏间隙。

### 工作原理

- 一个工作线程提前一帧 `fread` + `stbi_load_from_memory` 解码 JPG。
- UI 线程每帧执行一次 `nvgUpdateImage`，按 letterbox 等比适配绘制。
- 工作线程完成后排空缓冲，或触发 32 秒兜底定时器后 `popActivity(NONE)`，露出下面的主界面。
- 帧文件**不会**被提交到仓库 —— 顶层 `.gitignore` 会忽略 `resources/img/splash_frames/*`，只有 `.gitkeep` 被跟踪，目录保留但素材由你自备。

### 为什么用 JPG 序列而不是视频文件

`ffmpeg` 的 H.264 软解在 1080p 下需要 4 路 frame 线程才追得上，会占满 Switch 上用户可用的 3 个 A57 核心，让 Moonlight 的网络线程没核心可跑。720p 下 `stb_image` 解 JPG 每帧约 15–25 ms，单核心即可在 30 fps 的 33 ms / 帧预算内从容完成，剩下两个核心还能让 mDNS / HTTPS 配对 / RTSP 建立与启动动画并行进行。

---

## 致谢

上游 Moonlight-Switch 由 [XITRIX](https://github.com/XITRIX) 维护。本 fork 仅在其基础上新增了文档中描述的两个可选特性；渲染、串流、操控与各平台支持均为上游成果。

感谢 [Rock88](https://github.com/rock88) 的 [Moonlight-NX](https://github.com/rock88/moonlight-nx)，许多串流相关代码借鉴自此 👍。

[Xfangfang](https://github.com/xfangfang) 维护的 [Borealis](https://github.com/xfangfang/borealis) 库 —— 没有它就没有 iOS 移植版。

[Averne](https://github.com/averne) 为 [FFmpeg](https://github.com/averne/FFmpeg) 实现的 NVDEC 支持及对启用方式的指导。

也非常感谢 [Cooler3D](https://github.com/Cooler3Ds) 在 Deko3D 实现与性能问题上的协助。
