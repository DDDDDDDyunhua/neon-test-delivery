#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$0")"
target="${1:-Neon内核交付包-20261027}"
test ! -e "$target" || { echo "Target already exists: $target" >&2; exit 1; }
build=(neon-full-build.tar.part-*)
support=(neon-test-support.tar.part-*)
test "${#build[@]}" -eq 22 || { echo 'Missing full-build parts' >&2; exit 1; }
test "${#support[@]}" -eq 2 || { echo 'Missing support parts' >&2; exit 1; }
mkdir -p "$target/kernel"
cat "${build[@]}" | tar -xf - -C "$target/kernel"
cat "${support[@]}" | tar -xf - -C "$target"
(cd "$target" && python3 restore-linux-metadata.py && ln -s target/release kernel/bin)
echo "Complete uncompressed delivery restored at $target"
echo "Full outputs: kernel/target, kernel/build, kernel/pg_install"
