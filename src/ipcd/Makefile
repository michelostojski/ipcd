# Makefile — ipcd (IP Cam Daemon)
#
# Builds the single ipcd binary by compiling all sources in src/ and
# linking the Anyka SDK shared libraries.
#
# Web assets (web/*.html) are converted to C arrays under
# src/web_blobs/ via scripts/bin2c.sh during build. Edit web/*.html
# directly; `make` re-embeds them.
#
# Cross-compile env (override on the command line):
#   TOOLCHAIN  path with arm-anyka...-gcc           (default: ./anyka_uclibc_gcc/bin)
#   LIB_DIR    path with libapp_video.so etc.       (default: ./lib)
#
# Examples:
#   make
#   make TOOLCHAIN=/opt/anyka/bin LIB_DIR=/opt/anyka/lib
#   make clean
#   make syntax       (host syntax check, no Anyka libs needed)
#   make deploy DEPLOY_DIR=/mnt/sdcard/ipcd/bin

# -------------------------------------------------------------------
# Default goal — `make` with no args runs `make all`.
# This must come before any other target; otherwise the first rule
# Make sees becomes the default. (Pattern rules don't count, but
# concrete rules like $(BLOB_DIR): would.)
# -------------------------------------------------------------------
.DEFAULT_GOAL := all

# -------------------------------------------------------------------
# Toolchain
# -------------------------------------------------------------------
TOOLCHAIN ?= ./anyka_uclibc_gcc/bin
LIB_DIR   ?= ./lib

# Auto-detect cross GCC; override via the environment if needed.
CROSS_GCC ?= $(firstword $(wildcard $(TOOLCHAIN)/arm-anykav*-linux-uclibcgnueabi-gcc))
ifeq ($(CROSS_GCC),)
CROSS_GCC := $(firstword $(wildcard $(TOOLCHAIN)/arm-*-linux-uclibcgnueabi-gcc))
endif
ifeq ($(CROSS_GCC),)
CROSS_GCC := arm-linux-gnueabi-gcc
endif

CC      := $(CROSS_GCC)
STRIP   := $(patsubst %-gcc,%-strip,$(CROSS_GCC))

# -------------------------------------------------------------------
# Compile flags
# -------------------------------------------------------------------
INC      := -Iinclude -Isrc
CFLAGS   := -Os -Wall -Wextra -std=gnu99 \
            -ffunction-sections -fdata-sections \
            -Wno-format-truncation \
            -D_GNU_SOURCE $(INC)

# -------------------------------------------------------------------
# Link flags
#
# The Anyka SDK has *circular* dependencies between its shared libs
# (libplat_vqe needs symbols from libplat_thread, which calls back
# into libplat_osal, which calls back into libplat_log, etc). We
# wrap them in --start-group/--end-group so ld iterates until all
# undefined references resolve, instead of bailing on first miss.
#
# -ldl/-lm/-lrt are pulled in by some of the SDK libs at runtime via
# dlopen + math + clock_gettime; safer to list them explicitly.
#
# -rpath /usr/lib mirrors what main.sh exports as LD_LIBRARY_PATH on
# the camera, so a manual ./ipcd invocation finds the .so files even
# without the env var.
# -------------------------------------------------------------------
LDFLAGS  := -L$(LIB_DIR) \
            -Wl,--start-group \
               -lapp_video -lmpi_venc -lplat_vi \
               -lakv_encode -lapp_mem_ex \
               -lplat_vpss -lplat_isp_sdk -lplat_vqe \
               -lplat_mem -lplat_thread -lplat_osal \
               -lplat_log -lplat_dbg -lplat_common \
               -lplat_timer -lakmedia -lakaudiofilter \
               -lplat_ao -lmpi_adec -lapp_aenc_ex \
               -lplat_ai -lmpi_aenc \
               -lakaudiocodec \
            -Wl,--end-group \
            -lpthread -ldl -lm -lrt \
            -Wl,--gc-sections \
            -Wl,-rpath,/usr/lib \
            -Wl,-rpath-link,$(LIB_DIR)

# -------------------------------------------------------------------
# Sources
# -------------------------------------------------------------------
SRC_DIR    := src
WEB_DIR    := web
BLOB_DIR   := src/web_blobs
BIN2C      := scripts/bin2c.sh

C_SOURCES := \
    $(SRC_DIR)/main.c           \
    $(SRC_DIR)/wifi_cfg.c       \
    $(SRC_DIR)/wifi_ctrl.c      \
    $(SRC_DIR)/button.c         \
    $(SRC_DIR)/dns_spoof.c      \
    $(SRC_DIR)/led.c            \
    $(SRC_DIR)/timesync.c       \
    $(SRC_DIR)/http_srv.c       \
    $(SRC_DIR)/web_assets.c     \
    $(SRC_DIR)/cfgfile.c        \
    $(SRC_DIR)/auth.c           \
    $(SRC_DIR)/onvif.c          \
    $(SRC_DIR)/onvif_auth.c     \
    $(SRC_DIR)/onvif_wsd.c      \
    $(SRC_DIR)/onvif_events.c   \
    $(SRC_DIR)/snapshot.c       \
    $(SRC_DIR)/audio_out.c      \
    $(SRC_DIR)/audio_in.c       \
    $(SRC_DIR)/stats.c          \
    $(SRC_DIR)/ir.c             \
    $(SRC_DIR)/cap_pipeline.c   \
    $(SRC_DIR)/rtsp_server.c    \
    $(SRC_DIR)/onvif_ptz.c      \
    $(SRC_DIR)/ptz_motor.c

OBJS := $(C_SOURCES:.c=.o)

WEB_FILES := $(wildcard $(WEB_DIR)/*.html)
WEB_BLOBS := $(patsubst $(WEB_DIR)/%.html,$(BLOB_DIR)/%_html.h,$(WEB_FILES))

# -------------------------------------------------------------------
# Top-level targets
# -------------------------------------------------------------------
all: ipcd

ipcd: $(WEB_BLOBS) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	-$(STRIP) $@ 2>/dev/null || true
	@size $@ 2>/dev/null || true

clean:
	rm -f $(OBJS) ipcd
	rm -rf $(BLOB_DIR)

# -------------------------------------------------------------------
# Pattern rules
# -------------------------------------------------------------------
$(BLOB_DIR):
	mkdir -p $@

# bin2c symbol naming: web/index.html -> "index_html"
$(BLOB_DIR)/%_html.h: $(WEB_DIR)/%.html | $(BLOB_DIR)
	@echo "  EMBED  $<"
	@$(BIN2C) $*_html $< $@

# web_assets.c #includes the blob headers, so it has to wait for them.
$(SRC_DIR)/web_assets.o: $(WEB_BLOBS)

%.o: %.c include/ipcd.h
	$(CC) $(CFLAGS) -c -o $@ $<

# -------------------------------------------------------------------
# Convenience targets
# -------------------------------------------------------------------
DEPLOY_DIR ?= /tmp/sdcard/ipcd/bin
deploy: ipcd
	mkdir -p $(DEPLOY_DIR)
	cp ipcd $(DEPLOY_DIR)/

# Host syntax check — useful for catching include / signature issues
# without needing the cross toolchain or the Anyka libs. SDK calls
# remain undefined; we only check parsing + our internal API surface.
syntax: $(WEB_BLOBS)
	@for f in $(C_SOURCES); do \
	    echo "  SYN    $$f"; \
	    gcc $(INC) -fsyntax-only -Wall -Wextra -std=gnu99 -D_GNU_SOURCE $$f \
	        || exit 1; \
	done

.PHONY: all clean deploy syntax
