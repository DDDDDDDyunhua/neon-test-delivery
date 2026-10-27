#!/bin/bash
set -o pipefail
export PATH=/home/neon/.cargo/bin:/usr/local/bin:/usr/bin:/bin
export RUSTUP_DIST_SERVER=https://rsproxy.cn
export RUSTUP_UPDATE_ROOT=https://rsproxy.cn/rustup
export CARGO_BUILD_JOBS=4
export GIT_VERSION=source-archive-local-build
cd /opt/neon
make -j4 -s BUILD_TYPE=release CARGO_BUILD_FLAGS=--locked
