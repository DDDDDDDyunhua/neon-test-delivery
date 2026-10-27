#!/bin/bash
set -euo pipefail
if [ "$(id -u)" -ne 0 ]; then echo 'Run as root' >&2; exit 1; fi
if [ "$#" -ne 1 ]; then echo 'Usage: install.sh /path/to/kernel-directory' >&2; exit 1; fi
kernel_dir=$(readlink -f "$1")
assets=$(cd -- "$(dirname -- "$0")" && pwd)
test -d "$kernel_dir/bin"
test -d "$kernel_dir/pg_install/v16"
test -d "$kernel_dir/pg_install/v17"
for cmd in useradd runuser systemctl install; do command -v "$cmd" >/dev/null; done
test ! -e /opt/neon-single || { echo 'Existing /opt/neon-single: refusing to overwrite' >&2; exit 1; }
test ! -e /usr/local/bin/neon-single || { echo 'Existing neon-single command: inspect first' >&2; exit 1; }
test ! -e /etc/systemd/system/neon-single.service || { echo 'Existing service: inspect first' >&2; exit 1; }
# Restore Linux file modes and links before invoking this installer.
mkdir -p /opt/neon-single
cp -a "$kernel_dir" /opt/neon-single/kernel
id neon >/dev/null 2>&1 || useradd -m -s /bin/bash neon
chown neon:neon /opt/neon-single
install -m 644 "$assets/init.toml" /opt/neon-single/init.toml
install -m 755 "$assets/service.sh" /opt/neon-single/service.sh
install -m 755 "$assets/neon-single" /usr/local/bin/neon-single
install -m 644 "$assets/neon-single.service" /etc/systemd/system/neon-single.service
systemctl daemon-reload
echo 'Files installed. Run precheck.sh, then follow the single-host manual.'
echo 'No data was initialized and no service was started.'
