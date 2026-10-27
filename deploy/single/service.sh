#!/bin/bash
set -euo pipefail
case "${1:-}" in
  start)
    /usr/local/bin/neon-single start --start-timeout 60s
    /usr/local/bin/neon-single endpoint start main
    ;;
  stop)
    /usr/local/bin/neon-single stop
    ;;
  *) echo 'usage: service.sh start|stop' >&2; exit 2 ;;
esac
