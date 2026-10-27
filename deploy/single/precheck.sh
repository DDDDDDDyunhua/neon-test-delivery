#!/bin/bash
set -euo pipefail
test "$(uname -m)" = x86_64 || { echo 'This kernel package requires x86_64' >&2; exit 1; }
export LD_LIBRARY_PATH=/opt/neon-single/kernel/pg_install/v17/lib:/opt/neon-single/kernel/pg_install/v16/lib
failed=0
for file in /opt/neon-single/kernel/bin/* \
  /opt/neon-single/kernel/pg_install/v{16,17}/bin/{postgres,initdb,pg_ctl,psql} \
  /opt/neon-single/kernel/pg_install/v{16,17}/lib/neon*.so; do
  test -f "$file" || continue
  output=$(ldd "$file" 2>&1) || { echo "$file: $output"; failed=1; continue; }
  if [[ "$output" == *'not found'* ]]; then echo "$file: $output"; failed=1; fi
done
LC_ALL=C.UTF-8 locale charmap || failed=1
python3 -c 'import ctypes,sys; c=ctypes.CDLL(None,use_errno=True); r=c.syscall(436,100000,100001,0); print("close_range",r,"errno",ctypes.get_errno()); sys.exit(0 if r==0 else 1)' || failed=1
ss -lnt
df -h /opt/neon-single
echo 'Review port conflicts, disk capacity and host firewall before initialization.'
exit "$failed"
