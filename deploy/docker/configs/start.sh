#!/bin/bash
set -euo pipefail
role="$1"
case "$role" in
control-db)
 export PATH=/opt/neon-kernel/pg_install/v17/bin:$PATH
 if [ ! -s /data/pgdata/PG_VERSION ]; then
  initdb -D /data/pgdata -U neon --auth=trust --locale=C --encoding=UTF8
  echo "host all all 0.0.0.0/0 trust" >> /data/pgdata/pg_hba.conf
  pg_ctl -D /data/pgdata -o "-p 5432 -h 127.0.0.1" -w start
  createdb -h 127.0.0.1 -U neon storage_controller
  pg_ctl -D /data/pgdata -m fast -w stop
 fi
 exec postgres -D /data/pgdata -p 5432 -h 0.0.0.0
 ;;
controller)
 exec storage_controller --dev --listen 0.0.0.0:1234 --database-url postgresql://neon@control-db:5432/storage_controller --address-for-peers http://controller:1234 --timelines-onto-safekeepers --control-plane-url http://compute-hook:8080 --heartbeat-interval 1s --max-offline-interval 30s
 ;;
broker) exec storage_broker --listen-addr=0.0.0.0:50051 ;;
ps*)
 cp /configs/$role.toml /data/pageserver.toml
 printf 'id=%s\n' "${role#ps}" > /data/identity.toml
 exec pageserver -D /data
 ;;
sk*)
 id="${role#sk}"
 exec safekeeper -D /data --id "$id" --listen-pg=0.0.0.0:5454 --advertise-pg="$role:5454" --listen-http=0.0.0.0:7676 --availability-zone="az$id" --broker-endpoint=http://broker:50051
 ;;
compute*)
 version="${role#compute}"
 exec compute_ctl --dev --pgdata /data/pgdata --connstr postgresql://cloud_admin@127.0.0.1:5432/postgres --pgbin /opt/neon-kernel/pg_install/v$version/bin/postgres --compute-id "$role" --config /configs/$role.json --external-http-port 3080 --internal-http-port 3081
 ;;
esac
