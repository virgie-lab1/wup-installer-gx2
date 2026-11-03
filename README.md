# WUP Installer GX2 (Enhanced & 100% Offline)

[![Build and Release](https://github.com/virgie-lab1/wup-installer-gx2/actions/workflows/build.yml/badge.svg)](https://github.com/virgie-lab1/wup-installer-gx2/actions)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Environment](https://img.shields.io/badge/Wii%20U-Aroma%20%7C%20Tiramisu%20%7C%20HBL-brightgreen.svg)]()
[![Offline](https://img.shields.io/badge/Network-100%25%20Offline-orange.svg)]()

An enhanced, stable release of **WUP Installer GX2** for the Nintendo Wii U, supporting native **Aroma** (`.wuhb`), **Homebrew Launcher** (`.elf`), and **Channel** (`.rpx`) environments.

WUP Installer GX2 is an **entirely offline title installer** with a graphical interface derived from Loadiine GX2. It communicates directly with the Wii U's native `MCP` (Master Control Program) system calls to install games, game updates, DLC, and system titles from your SD card directly to internal system memory (**NAND**) or external **USB storage**.

---

## 🌟 Key Highlights & Bug Fixes

* **100% Offline (No Wi-Fi / Network Required):**
  * Zero dependencies on sockets, network drivers, or internet connections.
  * Perfect for offline setups, air-gapped systems, or consoles with physically damaged/defective Wi-Fi hardware that crash on other tools like NUSspli.
* **Batch Installation Stability Fix:**
  * Fixed a CPU spin-lock in `executeThread()` that pegged the CPU at 100% load during the countdown between titles, starving system I/O and background threads.
  * Added a retry and backoff loop when acquiring the `/dev/mcp` handle, preventing `"Failed to open MCP"` crashes when queueing multiple titles.
  * Explicitly deallocates memory buffers and zeroes pointers (`NULL`) after each title to prevent memory fragmentation and corruption.
  * Added an IOS filesystem and cache settling delay (`100ms`) between installs to allow the console's storage driver to flush write buffers to disk cleanly.
* **Aroma Support:**
  * Compiles natively to `.wuhb` for the modern Aroma custom firmware environment.
* **Controller Independence:**
  * Includes controller patches allowing full navigation with the Wii U Pro Controller, Classic Controller, or Wiimote without needing the Wii U GamePad.
* **Quality of Life Features:**
  * Supports installing titles from both `sd:/install` and `sd:/wudump`.
  * Optional checkbox to automatically delete installation files from the SD card after a successful install to reclaim storage.

---

## 💾 Installation Guide

### For Aroma Users (Recommended)
1. Download `wup_installer_gx2.wuhb` (or `wup_installer_gx2_SD_ready.zip`) from the [Releases](https://github.com/virgie-lab1/wup-installer-gx2/releases) page.
2. Copy `wup_installer_gx2.wuhb` into the `wiiu/apps/` folder on your SD card:
   ```text
   SD:/
   └── wiiu/
       └── apps/
           └── wup_installer_gx2.wuhb
   ```
3. Boot your Wii U with Aroma and launch **WUP Installer GX2** directly from the Wii U Home Menu.

### For Homebrew Launcher / Tiramisu Users
1. Download `wup_installer_gx2.elf`, `icon.png`, and `meta.xml`.
2. Place them into `wiiu/apps/wup_installer_gx2/` on your SD card:
   ```text
   SD:/
   └── wiiu/
       └── apps/
           └── wup_installer_gx2/
               ├── wup_installer_gx2.elf
               ├── icon.png
               └── meta.xml
   ```
3. Launch via the **Homebrew Launcher**.

---

## 📁 Preparing Titles on Your SD Card

Titles to install must be placed in their own folder inside `sd:/install/`:

```text
SD:/
└── install/
    ├── Mario Kart 8 [Game]/
    │   ├── 00000000.app
    │   ├── 00000001.app
    │   ├── title.cert
    │   ├── title.tik
    │   └── title.tmd
    └── Game Update [Patch]/
        ├── 00000000.app
        ├── title.tik
        └── title.tmd
```

> [!TIP]
> If installing to an external mechanical hard drive (HDD), always ensure it is powered via a **USB Y-cable** or dedicated external power adapter. The Wii U's USB ports output only 500mA, which can drop during sustained write operations.

---

## 🛠️ Building the Application

### Option A: Automatic Cloud Builds (GitHub Actions)
This repository includes a continuous integration workflow (`.github/workflows/build.yml`) utilizing devkitPro's official container:

1. **Fork** this repository to your GitHub account.
2. To create a new release, create and push a tag:
   ```shell
   git tag v1.5.0
   git push origin v1.5.0
   ```
3. GitHub Actions will automatically compile the project, package the SD-ready zip, and publish a **GitHub Release** with all binaries attached.

### Option B: Local Docker Build
If Docker is installed on your machine, compile without installing any toolchains:
```shell
docker buildx build . -t wupgx2 --load
docker run -it --rm -v "$PWD":/app wupgx2
```

### Option C: Manual devkitPro Build
Requires [wut](https://github.com/devkitPro/wut) and devkitPPC portlibs:
```shell
dkp-pacman -S wut-tools ppc-zlib ppc-libmad ppc-libogg ppc-libgd ppc-freetype \
              ppc-brotli ppc-libjpeg-turbo ppc-libpng ppc-libvorbisidec ppc-glm ppc-bzip2
make -j$(nproc)
```

---

## 👥 Credits & Acknowledgments

* **Dj_Skual** — Original creator of WUP Installer GX2 with the Loadiine GX2 GUI base.
* **Fangal-Airbag** — Modern Aroma port and `.wuhb` maintenance.
* **brienj (xhp-creations)** — Original RPX port.
* **GaryOderNichts** — Wii U controller mod implementation.
* **Yardape8000** — WUP Installer Y Mod base.
* **dimok789** — Core foundation work on HBL, Loadiine, and WUP installer internals.
* **Maschell & the Wii U Homebrew Environment** — Aroma environment, WUT, and toolchains.
