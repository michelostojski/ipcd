> [!CAUTION]
> # Use at your own RISK!
> Make sure you know what this software does and how it does it before attemping to flash anything!

# ipcd — Custom firmware for Anyka AK39EV330 IP cameras

Open-source replacement of the proprietary `anyka_ipc` binary that ships
on a number of cheap "cloud" IP cameras built around the Anyka **AK39EV330**
SoC (the test bed here is a Surfola WS01 camera with an SC2331 sensor
and an ATBM6031 dual-VIF Wi-Fi chip, but the same approach should work
on any AK39EV330 board with the same SDK version).

`ipcd` is a single-binary daemon that handles **everything** the stock
firmware did — Wi-Fi provisioning (STA + AP fallback with captive
portal), NTP sync, reset button, status LEDs, video capture from the
sensor, H.264/H.265 encoding — but exposes the streams over **standard
RTSP** on port 8554 and a small **HTTP UI** on port 80 with live HLS
preview, stats, and Wi-Fi setup. No cloud, no apps, no telemetry.

```
rtsp://<camera-ip>:8554/main      1920x1080 H.264/H.265
rtsp://<camera-ip>:8554/sub       640x360   H.264
http://<camera-ip>/               Wi-Fi setup, stats, /live preview
```

> **Status:** working daily-driver on the author's hardware. Plenty of
> rough edges — see _Known issues_ at the bottom.

---

## What's in this repo

| Path                          | Contents                                                     |
|-------------------------------|--------------------------------------------------------------|
| `src/ipcd/`                   | ipcd source code (C, builds with the Anyka uClibc toolchain) |
| `src/x-tools.tar.bz2`         | crosstool-ng compiled toolchain (.config included in src)    |
| `firmware/dumps/rootfs.bin`   | Original SPI-flash ROOTFS partition dump (squashfs)          |
| `firmware/dumps/app.bin`      | Original SPI-flash APP partition dump (squashfs)             |
| `firmware/patched/app.bin`    | Modified APP partition with ipcd, ready to flash             |
| `ghidra/`                     | Ghidra decompilations of relevant Anyka SDK libs             |

The original dumps are included so you can always go back to stock if
something goes wrong, and so anyone with the same hardware can rebuild
their own modified APP without having to dump their own flash first.

---

## TL;DR for the impatient

If you have the same camera and just want to flash it:

1. Open the camera, find the SPI flash (8-pin SOIC).
2. Dump the original flash with a CH341A programmer + 3.3 V level
   shifter — back it up somewhere safe.
3. Flash `firmware/patched/app.bin` to the **APP** partition only
   (offset `0x40C000`, length `4048 KB`). Leave UBOOT, ENV, DTB,
   KERNEL, ROOTFS, CONFIG untouched.
4. Reassemble, power on, look for an open Wi-Fi called `AK_IPC` (password `11111111`),
   connect, follow the captive-portal prompt to enter your home
   Wi-Fi credentials.
5. Once the camera joins your network, point VLC at
   `rtsp://<camera-ip>:8554/main`.

### TL;DR (x2)
1. Copy the app.bin and the agingtest directory (with the 
   contained aging_test script) to a fat32 formatted sd-card.
2. Boot the camera with the sd card inserted.
3. Prey it works and continue on step 4 on the previous TL;DR

If you want to know **why** that works or how to do it from scratch on
your own dump — keep reading.

---

## The hacking process (long version)

### 1. Hardware: dumping the flash

The whole firmware lives in a single 16 MB SPI NOR flash chip on the
PCB. To get a copy out you need:

- A **CH341A** USB programmer (the cheap $5 ones on AliExpress work).
- A **3.3 V logic-level shifter**. _Don't skip this._ The CH341A
  natively drives the data lines at 5 V on most clones, which will
  eventually kill the flash chip and possibly the SoC. A small adapter
  board with an LDO regulator and a level shifter is cheap insurance.
- An **SOIC-8 test clip** so you don't have to desolder the chip.

Power the camera off, clip the chip, run something like
[`flashrom`](https://flashrom.org) or the official CH341A GUI
(`AsProgrammer`, `NeoProgrammer`) and read the full 16 MB to a file.
**Read it twice and diff the two dumps** — if they don't match
byte-for-byte, your wiring is flaky and you need to fix it before
trusting any of the data.

### 2. Finding the partition layout

The flash has no partition table of its own; the layout is hard-coded
in U-Boot's environment as an `mtdparts` string. The fastest way to
find it is `strings`:

```sh
strings full.bin | grep mtdparts
```

On the camera in this repo that yields:

```
mtdparts=spi0.0:256K@0x0(UBOOT),4K@0x40000(ENV),4K@0x41000(ENVBK),
         48K@0x42000(DTB),1800K@0x4e000(KERNEL),1632K@0x210000(ROOTFS),
         400K@0x3a8000(CONFIG),4048K@0x40C000(APP)
```

Decoded:

| Partition | Offset       | Size     | Filesystem | Mounted at |
|-----------|--------------|----------|------------|------------|
| UBOOT     | `0x000000`   | 256 KB   | raw        | —          |
| ENV       | `0x040000`   |   4 KB   | u-boot env | —          |
| ENVBK     | `0x041000`   |   4 KB   | u-boot env | —          |
| DTB       | `0x042000`   |  48 KB   | flat DTB   | —          |
| KERNEL    | `0x04E000`   | 1800 KB  | uImage     | —          |
| ROOTFS    | `0x210000`   | 1632 KB  | squashfs   | `/`        |
| CONFIG    | `0x3A8000`   | 400 KB   | jffs2      | `/etc/config` |
| APP       | `0x40C000`   | 4048 KB  | squashfs   | `/usr` _(via overlay)_ |

`dd` the regions out:

```sh
dd if=full.bin of=rootfs.bin bs=1 skip=$((0x210000)) count=$((1632*1024))
dd if=full.bin of=config.bin bs=1 skip=$((0x3a8000)) count=$((400*1024))
dd if=full.bin of=app.bin    bs=1 skip=$((0x40c000)) count=$((4048*1024))
```

ROOTFS and APP are squashfs — `sudo unsquashfs rootfs.bin` and
`sudo unsquashfs app.bin`. CONFIG is jffs2 (`jefferson` works, or `mount -t
jffs2 -o loop` with the right `mtdram` setup if you really want).

### 3. Getting root

Browsing through the unsquashed rootfs, the boot script
`/usr/sbin/main.sh` does something like:

```sh
if [ -f /mnt/agingtest/aging_test ]; then
    /mnt/agingtest/aging_test
elif [ -f /mnt/debug/debug.sh ]; then
    ...
else
    /usr/bin/anyka_ipc &     # the production path
fi
```

That first branch is the factory aging-test mode. It runs whatever
script lives at `/mnt/agingtest/aging_test`, **as root**, before any
of the production daemons start. `/mnt` is the SD card. So:

1. Format an SD card FAT32.
2. `mkdir -p /mnt/agingtest && echo '#!/bin/sh' > aging_test &&
    echo 'sh' >> aging_test && chmod +x aging_test`
3. Insert the card, power on the camera, attach a UART cable —
   you land in a root shell.

(There are obviously more elegant paths to root: serial U-Boot
console, kernel command-line edit, etc. The aging-test trick is just
the laziest.)

Once you have a shell, you can replace `/etc/config/shadow` with one
that has a known root password, then access the device over SSH if
you ever start `dropbear` from the boot scripts. The cleanest way to
make root access permanent is to `dd` the modified ROOTFS back to the
flash partition on `/dev/mtd5` (or whatever the kernel calls it on
your unit — `cat /proc/mtd` will tell you).

```sh
# DANGER. Triple-check the partition number.
dd if=/mnt/rootfs_modified.bin of=/dev/mtd5 bs=4096
```

### 4. Reverse-engineering the SDK

With root in hand, the goal becomes _replacing_ `anyka_ipc` so we can
do something useful with the video stream. `anyka_ipc` is a closed
binary that talks to a proprietary cloud (Danale, in this case) — it
captures from the sensor, encodes, and streams to "their" servers.
There is no documented way to ask it for a local RTSP feed.

The shared libraries it links against — `libapp_video.so`,
`libplat_vi.so`, `libmpi_venc.so`, `libplat_mem.so`,
`libplat_vpss.so`, `libplat_isp_sdk.so`, `libplat_vqe.so`, etc. —
**are** present on the device but the headers are not. So:

1. Pull the `.so` files off the camera.
2. Drop them in [Ghidra](https://ghidra-sre.org/) and decompile.
3. Cross-reference with the boot-time debug log of the stock
   `anyka_ipc` (it logs the exact sequence of SDK calls in
   `hal_video_init` if you crank up the log level), and derive
   prototypes by hand.

The Ghidra outputs that turned out to matter most are checked into
`ghidra/` in this repo:

- `libapp_video.so` — `ak_app_video_bind_chn`, `ak_app_video_venc_get_stream`, …
- `libplat_vi.so` — `ak_vi_open`, `ak_vi_load_sensor_cfg`, `ak_vi_enable_dev`, …
- `libmpi_venc.so` — `ak_venc_open`, `ak_venc_release_stream`, …
- `libplat_mem.so` — `ak_mem_dma_pool_create`, `ak_mem_dma_pool_activate`, …
- `libplat_vpss.so` — `ak_vpss_set_auto_day_night_param`, day/night detector, …
- `libplat_isp_sdk.so` — exposure/gain knobs, AE, anti-flicker, …
- `libplat_vqe.so` — image processing pipeline (denoise, dewarp, etc.)

None of those headers exist anywhere on the public internet. We're
building against shadow prototypes that are believed-to-match the
binary ABI, with the only validation being "the camera doesn't crash
and the picture looks correct."

#### Side quest: the existing open-source SDK didn't help

Our first instinct was to reuse what already exists. The community has
a couple of open RTSP/streaming binaries for older Anyka chipsets:

- [`MuhammedKalkan/Anyka-Camera-Firmware`](https://github.com/MuhammedKalkan/Anyka-Camera-Firmware)
  — RTSP server for AK3918-class cameras.
- [`Gerge/Anyka_ak3918_hacking_journey`](https://gitea.raspiweb.com/Gerge/Anyka_ak3918_hacking_journey/)
  — full alternative rootfs.

Neither worked here. The AK39EV330 (v330) ships a newer SDK whose
function signatures don't match the AK3918 (v200/v210) ones:

- Recompiling Kalkan's RTSP server with a fresh toolchain that matched
  our uClibc/libiconv versions produced a binary that linked but
  segfaulted as soon as it called into `libapp_video`. The Anyka
  symbols had moved or changed shape between SDK versions.
- Dropping in Gerge's full rootfs booted the camera, but the kernel
  and the in-kernel sensor/ISP modules were too new for the v330
  drivers, so video never came up.

So we ended up writing our own.

### 5. The road from `proxy_capture` to `ipcd`

The current ipcd binary did not appear in one go. It grew through
several intermediate stages, each of which solved one problem at a
time. We're keeping the trail because the failures are at least as
informative as the working code.

#### Stage 1 — `proxy_capture` (TCP firehose)

The very first prototype was a tiny C program that did the bare
minimum: bring up VI + VENC, grab encoded frames, and dump them to a
TCP socket over a homemade wire protocol. A Python script on a PC
caught the bytes, repackaged them as RTP, and ran a small RTSP server
locally so VLC could play them.

This was useful as a learning vehicle (you could iterate on the RTSP
side in Python without touching cross-compilation), but it had a
predictable list of problems: extra latency, two moving parts to keep
running, and HEVC playback in VLC was unreliable because RTP
packetization is fiddly to get right in a high-level language.

**Key lessons** that survived into the final version:

- The exact Anyka SDK init sequence (`mem_init` → `dma_pool_create`
  → `dma_pool_activate` → `vi_open` → `load_sensor_cfg` →
  `set_dev_attr` → `enable_dev` → `enable_chn` → `venc_open` →
  `bind_chn`). Skipping any step or reordering them makes the encoder
  silently emit zero frames.
- The DMA pool **must** be set up via the low-level `libplat_mem.so`
  API (`ak_mem_dma_pool_create` + `ak_mem_dma_pool_activate`), NOT
  the high-level `libapp_mem_ex.so` API
  (`set_vi_policy`/`set_venc_policy`/`activate`). The latter
  pre-reserves fixed-size buffers and the encoder's runtime DMA
  requests don't match those sizes, so you get
  `"No enough space in the pool"` errors at random.
- VENC frame-type 1 (H.264) and 3 (HEVC IDR) are both keyframe
  boundaries — keep this in mind when packetizing.

#### Stage 2 — `proxy_capture` with embedded RTSP

The Python proxy got rewritten as a ~600-line C module
(`rtsp_server.c`) inside the same binary. RTSP is actually trivial as
a protocol (it's basically a few text commands and one SDP blob); the
hard part is RTP packetization (FU-A for H.264, FU for HEVC) and
getting the SPS rewriter right so VLC can actually start playback
from any IDR.

After that it was a single binary, no Python. You'd run
`proxy_capture` and `vlc rtsp://camera:8554/main` worked.

But Wi-Fi and reset and provisioning were still being handled by the
OEM scripts (which we'd hijacked via the aging-test branch). And
those OEM scripts were also responsible for keeping `anyka_ipc`
alive, so we were in this awkward state where two things were
fighting over the same hardware.

#### Stage 3 — `proxycam` supervisor

Next iteration split things into two processes: `proxy_capture`
(unchanged) plus a new `proxycam` supervisor that handled

- Wi-Fi STA mode (read `/etc/config/wifi.conf`, run `wpa_supplicant`
  + `udhcpc`),
- Wi-Fi AP fallback when no creds are saved (run `hostapd` +
  `udhcpd`, expose a tiny HTTP UI on `10.1.8.1` for setup),
- captive-portal redirects so phones popped up "Sign in to network"
  automatically,
- NTP one-shot after STA came up,
- the reset button (long-press on `/dev/input/event0` wipes
  `wifi.conf` and reboots),
- the status LEDs,
- forking, monitoring, and re-launching `proxy_capture` as a child.

This worked but it had two daemons sharing the Anyka SDK lifecycle
through fork/exec, an `LD_LIBRARY_PATH`, and a private IPC channel.
Lots of edge cases (what if `proxy_capture` segfaults at startup
because the pool isn't ready yet? what if Wi-Fi drops while
streaming?).

#### Stage 4 — `ipcd` (current)

Final iteration collapses everything into one process and one
binary. Modules, all in the same address space, no IPC:

- **`main.c`** — netmgr state machine (boot → AP/provisioning →
  STA-connecting → online → reconfigure → …), signal handling, glue.
- **`wifi_cfg.c` / `wifi_ctrl.c`** — load/save credentials, drive
  `wpa_supplicant`/`hostapd`/`udhcpc`/`udhcpd`.
- **`dns_spoof.c`** — tiny DNS server in AP mode that answers _every_
  query with our AP IP, so the phone's captive-portal probe lands on
  our HTTP server.
- **`button.c`** — `/dev/input/event0` watcher, long-press = factory
  reset.
- **`led.c`** — `/sys/class/leds/{blue,red,wifi_pwr,irled}/brightness`
  policy.
- **`timesync.c`** — one-shot `ntpd -nq` then keeps a daemon.
- **`cap_pipeline.c`** — VI/VENC pipeline (the old `proxy_capture`
  logic) running as a supervised thread.
- **`rtsp_server.c`** — RTSP/RTP on `:8554`, multi-client.
- **`ir.c`** — autonomous day/night detector + IR-LED via
  `/sys/class/leds/irled/brightness`.
- **`stats.c`** — 1 Hz sampler, 60 s ring buffer, JSON serializer for
  the stats UI.
- **`http_srv.c`** — HTTP/1.1 on `:80` serving the JSON API and the
  embedded UI.
- **`onvif*.c`** — ONVIF Protocol.
- **`web_assets.c`** — HTML/CSS/JS embedded at build time via a tiny
  `bin2c` script. Optional runtime override
  (`IPCD_WEB_RUNTIME=1`) reads from `/mnt/ipcd/web/` so you can
  iterate on the UI without recompiling.
- **`cfgfile.c`** — INI loader for `/etc/config/ipcd.conf` (atomic
  save: write to `.tmp`, `fsync`, `rename`).

Build is one `make` away (see below); deploy is `cp ipcd /usr/bin/`
inside a rebuilt APP squashfs, plus a one-line edit to `main.sh` that
launches `ipcd` instead of `anyka_ipc`.

---

## Building from source

You need:

- A compatible toolchain, either the Anyka uClibc toolchain 
  (`MuhammedKalkan/Anyka-Camera-Firmware` repo has a working copy of
  `arm-anykav*-linux-uclibcgnueabi-gcc`) or the compressed one in the 
  `x-tools.tar.bz2` will do.
- The Anyka SDK shared libraries (`libapp_video.so`, `libplat_*.so`,
  …). These come **straight off the app partition of the camera**.
- Standard host tools: `make`, `squashfs-tools` (`mksquashfs`).

```sh
cd src/ipcd
make TOOLCHAIN=/path/to/anyka_uclibc_gcc/bin LIB_DIR=/path/to/camera-libs
```

Output: a single stripped `ipcd` binary, ~120 KB.

You can also run `make syntax` on the host with no toolchain — that
runs the system `gcc` in `-fsyntax-only` mode for sanity checks.

---

## Repackaging the firmware

Once you have `ipcd` built, you have to get it onto the camera.

### Option A — quick, no flashing (good for development)

Drop the binary on the SD card and short-circuit the boot script:

```sh
# host
mkdir -p /mnt/sdcard/ageingtest/
cp src/ipcd/ipcd /mnt/sdcard/ipcd

# /mnt/agingtest/aging_test on the SD card:
#!/bin/sh
export LD_LIBRARY_PATH=/usr/lib:/usr/local/lib:$LD_LIBRARY_PATH
exec /mnt/ipcd
```

Pop the card in, power on, you're running ipcd. Camera reverts to
stock the moment you remove the card.

### Option B — flash a modified APP partition (production)

1. Unsquash the original APP:
   ```sh
   unsquashfs -d app_extracted firmware/dumps/app.bin
   ```
2. Drop in the new binary and patch `main.sh`:
   ```sh
   rm app_extracted/bin/anyka_ipc
   cp src/ipcd/ipcd app_extracted/bin/
   # Edit app_extracted/sbin/main.sh: in the final `else` branch,
   # replace `/usr/bin/anyka_ipc &` with `/usr/bin/ipcd &`.
   ```
3. Repack as squashfs **with the same compression and block size as
   the original** — otherwise the kernel's squashfs driver will refuse
   to mount it. For the AK39EV330 stock image that's xz with a 128 KB
   block size:
   ```sh
   mksquashfs app_extracted app_new.bin -comp xz -b 131072 -noappend -no-progress
   ```
4. Pad to exactly 4048 KB (the partition size) with `0xFF`:
   ```sh
   truncate -s 4145152 app_new.bin
   # or: dd if=/dev/zero bs=1 count=$((4145152-$(stat -c%s app_new.bin))) >> app_new.bin
   ```
5. Flash to offset `0x40C000` of the SPI flash with the CH341A.

`firmware/patched/app.bin` in this repo is the result of running
those steps with the matching `ipcd` binary. If you flash that as-is
(without rebuilding), make sure your camera is the same model with
the same Anyka SDK version — otherwise the `.so` ABI may not match
and ipcd will crash at startup.

### Option C — flash from u-boot (no programmer)

copy **app_new.bin** to sd card and rename as **usr.sqsh4**
insert the sd card in the camera and start the camera with the serial console connected.
Stop the boot and execute the command **tfdownsquashfs**, it will automatically flash the app partition. Then execute the command **reset** to reboot with the new firmware.

**This is irreversible without a programmer if it goes wrong.** Make
sure you have a known-good `app.bin` on the SD card so worst-case you
can re-flash from the bricked camera's serial console in U-Boot.

### Option D — flash from inside the running camera (no programmer)
 
Once you have root, you can write the new APP partition straight
from the camera, without unsoldering anything:
 
```sh
# Identify which /dev/mtdblockN is APP (look with mount command)
# Copy app_new.bin to the camera (via SD card or scp), then:
dd if=/mnt/app_new.bin of=/dev/mtdblock
sync
reboot
```
 
**This is irreversible without a programmer if it goes wrong.** Make
sure you have a known-good `app.bin` on the SD card so worst-case you
can re-flash from the bricked camera's serial console in U-Boot.

---

## First boot

On first boot ipcd looks for `/etc/config/wifi.conf`. If it's missing
or incomplete:

1. ipcd starts `hostapd` on `wlan1` with the SSID in the hostapd.conf file 
   (usually `AK_IPC` with password `11111111`)
2. ipcd starts `udhcpd` to hand out `10.1.8.x` leases.
3. The internal DNS spoofer answers every query with `10.1.8.1`, so
   any phone-side captive-portal probe (`connectivitycheck.gstatic.com`,
   `captive.apple.com`, `msftconnecttest.com`, …) lands on ipcd's
   HTTP server.
4. The phone pops up the "Sign in to network" notification, opens a
   browser to ipcd's setup page, you pick your home Wi-Fi and enter
   the password.
5. ipcd writes `/etc/config/wifi.conf`, switches to STA mode,
   associates, runs `udhcpc`, and is online.

After that, a quick visit to `http://<camera-ip>/` shows the stats
and `/live` page. RTSP is up on port 8554.

If you ever need to start over: hold the reset button for ≥5 seconds.
ipcd wipes `wifi.conf` and reboots back to AP mode.

---

## Endpoint summary

| URL                         | Method | Notes                                           |
|-----------------------------|--------|-------------------------------------------------|
| `/`                         | GET    | Wi-Fi setup UI (also stats UI when online)      |
| `/stats`                    | GET    | Stats UI (FPS, bitrate, RSS, RTSP clients)      |
| `/live`                     | GET    | HLS preview (latency 6–10 s)                    |
| `/api/status`               | GET    | JSON: state, ssid, ip, ir mode                  |
| `/api/stats`                | GET    | JSON: per-stream metrics + 60 s history         |
| `/api/scan`                 | GET    | Wi-Fi scan results                              |
| `/api/save`                 | POST   | Save SSID/PSK and re-provision                  |
| `/api/ir`                   | POST   | Body: `mode=auto\|off\|night`                   |
| `rtsp://<host>:8554/main`   | —      | Main stream (1080p)                             |
| `rtsp://<host>:8554/sub`    | —      | Sub stream (360p)                               |

---

## Known issues / open points

- **HEVC + VLC**: VLC has long-standing bugs playing HEVC RTSP streams
  from embedded cameras. We default both streams to H.264 for
  compatibility.
- **Coexistence with stock provisioning**: some OEM flavours of this
  hardware run a separate `cmd_serverd` that decrypts Wi-Fi credentials
  from a factory partition and brings up `wlan0` _before_ ipcd's
  state machine takes over. ipcd now detects an already-associated
  STA and skips the AP fallback in that case, but it's worth knowing
  if you see "deauthenticating from … by local choice" in dmesg the
  first time you boot.
- **ONVIF**: very partial — only what was needed to make a couple of
  popular NVR clients happy.

---

## Credits / prior art

- [`MuhammedKalkan/Anyka-Camera-Firmware`](https://github.com/MuhammedKalkan/Anyka-Camera-Firmware)
  — first attempt at the streaming binary, and the toolchain reference.
- [`Gerge/Anyka_ak3918_hacking_journey`](https://gitea.raspiweb.com/Gerge/Anyka_ak3918_hacking_journey/)
  — alternative rootfs, useful as a comparison point even though it
  wasn't directly usable on v330.
- The Anyka v330 SDK itself, which we never actually had — only the
  binary `.so` files on the device. Everything in `ghidra/` is a
  best-effort reconstruction. Corrections welcome.

---

## License

ipcd is released under the MIT license (see `LICENSE`).

The original firmware dumps in `firmware/dumps/` are included for
research and interoperability purposes only. They are © Anyka and the
camera vendor; we do not claim any rights to them, and we redistribute
them on the understanding that doing so falls under the legal
exceptions for reverse engineering for interoperability in your
jurisdiction. Do your own homework before basing a commercial product
on any of this.
