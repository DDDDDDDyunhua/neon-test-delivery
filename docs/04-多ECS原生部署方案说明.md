# 8 台 ECS 原生部署：角色、关联和启动顺序

本文是多机实施方案，不是已完成的自动部署工具。当前内核已用于单机和 Docker 模拟集群，尚未在 8 台真实 ECS 执行验证。配置 API 以本批内核为准。

## 1. 机器分工

| ECS | 示例私网 IP | 角色 |
| --- | --- | --- |
| ECS1 | 10.0.0.11 | controller 元数据库、broker、controller、compute 通知适配服务 |
| ECS2 | 10.0.0.12 | pageserver，ID=1 |
| ECS3 | 10.0.0.13 | pageserver，ID=2 |
| ECS4 | 10.0.0.14 | safekeeper，ID=1 |
| ECS5 | 10.0.0.15 | safekeeper，ID=2 |
| ECS6 | 10.0.0.16 | safekeeper，ID=3 |
| ECS7 | 10.0.0.17 | PG16 compute |
| ECS8 | 10.0.0.18 | PG17 compute |

每台解压同一内核包到 `/opt/neon/kernel`，安装匹配的原生运行库。以普通用户 neon 运行，独立数据放 `/var/lib/neon/<角色>`，配置放 `/etc/neon`；目录需要预先创建并授予 neon 权限。统一设置 PATH 包含 kernel/bin，LD_LIBRARY_PATH 包含 PG16/17 的 lib。不同进程使用独立 systemd 单元；不能复用单机 neon_local 的整个实例控制单元。

## 2. 网络与存储前提

要求 VPC 私网互通和稳定的节点地址。broker 50051；controller 1234；pageserver PG/HTTP/gRPC 6400/9898/51051；safekeeper PG/HTTP 5454/7676；compute SQL 5432、管理端口 3080/3081；通知适配服务 8080。内部接口限制在对应节点之间，不对公网开放。controller 元数据库在 ECS1 本机 5432。

两个 pageserver 必须访问同一套持久化后端。可选共同的兼容对象存储，或经过验证的共享文件系统；不能分别使用两台机器各自的同名本地目录来模拟共享。

下文仅以共享文件系统均挂载 `/mnt/neon-shared` 说明地址关系，并未提供或验收共享文件系统的安装方案。若暂时只有各自本地盘，应先以一个主 pageserver 验证跨机数据链路，不承诺双 pageserver 迁移。使用 OBS 需另行验证其对象存储接口与本内核兼容性。

## 3. 启动顺序

```text
全部机器依赖/权限/网络 + 共享持久层准备
  → ECS1 元数据库、broker、通知服务、controller 进程
  → ECS2/3 pageserver 与 ECS4/5/6 safekeeper（可并行）
  → 注册存储节点、等待整体就绪
  → 创建 tenant/timeline，生成并分发 compute spec
  → ECS7/8 compute（可并行）
  → SQL、单 SK 故障、迁移、整套恢复验收
```

controller 进程先运行，不代表要等它完全 healthy 才运行 pageserver。已有集群恢复时两者需要相互协调，应避免环形等待。正常重启不重新 init 元数据库，不重新创建身份和租户。

## 4. ECS1：控制面

首次用包内 PG17 的 initdb 创建 `/var/lib/neon/control-db`，以用户 neon、本机 5432 启动，并创建 `storage_controller` 数据库。此元数据库不同于业务 PG，详细命令形式可参考单机手册；多机应使用以下显式服务启动方式而非 neon_local。

分别启动独立服务：

```bash
storage_broker --listen-addr=10.0.0.11:50051
```

通知服务需监听 10.0.0.11:8080，并把 PG16/17 的 tenant 映射至 `http://10.0.0.17:3080`、`http://10.0.0.18:3080`。它持有签名私钥，compute 配置含匹配的 JWKS。

```bash
storage_controller --dev \
  --listen 10.0.0.11:1234 \
  --database-url postgresql://neon@127.0.0.1:5432/storage_controller \
  --address-for-peers http://10.0.0.11:1234 \
  --timelines-onto-safekeepers \
  --control-plane-url http://10.0.0.11:8080 \
  --heartbeat-interval 1s --max-offline-interval 30s
```

Docker 配套里的 hook.py 使用容器 DNS 和同机挂载配置，不能原样用于真实多机；需要改成稳定 IP/域名、租户到 compute 的映射、配置持久化和分发。本批未交付这部分多机改造程序。无通知链路时不能把迁移后的自动跟随作为已支持能力。

## 5. ECS4/5/6：safekeeper

ECS4：

```bash
safekeeper -D /var/lib/neon/safekeeper \
  --id 1 \
  --listen-pg=10.0.0.14:5454 \
  --advertise-pg=10.0.0.14:5454 \
  --listen-http=10.0.0.14:7676 \
  --availability-zone=az1 \
  --broker-endpoint=http://10.0.0.11:50051
```

ECS5/6 分别替换 id=2/3、IP=10.0.0.15/16、可用区标识=az2/az3。节点 ID 唯一，WAL 目录各自独立。advertise 地址必须能被其他 ECS 访问。标识不同不代表物理上已经跨可用区。

## 6. ECS2/3：pageserver

在 `/var/lib/neon/pageserver/identity.toml` 写 ECS2 的 `id=1`，ECS3 写 `id=2`。ECS2 的 `pageserver.toml` 示例：

```toml
pg_distrib_dir = '/opt/neon/kernel/pg_install'
broker_endpoint = 'http://10.0.0.11:50051'
control_plane_api = 'http://10.0.0.11:1234/upcall/v1/'
listen_pg_addr = '10.0.0.12:6400'
listen_http_addr = '10.0.0.12:9898'
listen_grpc_addr = '10.0.0.12:51051'
pg_auth_type = 'Trust'
http_auth_type = 'Trust'
grpc_auth_type = 'Trust'
remote_storage = { local_path = '/mnt/neon-shared/pageserver' }
virtual_file_io_engine = 'std-fs'
virtual_file_io_mode = 'buffered'
no_sync = false
page_cache_size = 16384
```

ECS3 替换三个监听地址为 10.0.0.13，共同的 broker/controller/持久层保持一致。分别执行：

```bash
pageserver -D /var/lib/neon/pageserver
```

Trust/dev 配置只适用于隔离测试网络。

## 7. 注册和创建租户（在管理节点执行）

示例注册 ps1：

```bash
curl -f -X POST http://10.0.0.11:1234/control/v1/node \
  -H 'Content-Type: application/json' \
  -d '{"node_id":1,"listen_pg_addr":"10.0.0.12","listen_pg_port":6400,"listen_http_addr":"10.0.0.12","listen_http_port":9898,"listen_grpc_addr":"10.0.0.12","listen_grpc_port":51051,"availability_zone_id":"az1"}'
```

ps2 替换节点 ID、地址和实际可用区。

示例注册 sk1：

```bash
curl -f -X POST http://10.0.0.11:1234/control/v1/safekeeper/1 \
  -H 'Content-Type: application/json' \
  -d '{"id":1,"region_id":"local","version":1,"host":"10.0.0.14","port":5454,"http_port":7676,"availability_zone_id":"az1"}'
```

sk2/3 同时修改 URL ID、请求体 ID、地址和可用区。确认各节点状态后创建 tenant/timeline：

```bash
TENANT_ID=$(python3 -c 'import uuid; print(uuid.uuid4().hex)')
TIMELINE_ID=$(python3 -c 'import uuid; print(uuid.uuid4().hex)')
curl -f -X POST http://10.0.0.11:1234/v1/tenant \
  -H 'Content-Type: application/json' \
  -d "{\"new_tenant_id\":\"$TENANT_ID\",\"placement_policy\":{\"Attached\":1}}"
curl -f -X POST "http://10.0.0.11:1234/v1/tenant/$TENANT_ID/timeline" \
  -H 'Content-Type: application/json' \
  -d "{\"new_timeline_id\":\"$TIMELINE_ID\",\"pg_version\":16}"
```

保存身份及响应。PG17 另建一组 ID，pg_version=17。以响应中的实际放置和 membership/generation 生成 compute 配置，不能假定 PG16 一定放 ps1 或写死 generation。

## 8. ECS7/8：计算节点

生成当前内核格式的 compute spec 后分发到各自 `/etc/neon/compute16.json`、`compute17.json`。spec 至少包含 PG/角色配置、tenant/timeline、实际 pageserver 地址、3 个 safekeeper 地址及 generation、JWKS。该 JSON 不是 postgres.conf；本批尚无多机专用的 spec 生成和分发脚本。

ECS7：

```bash
compute_ctl --dev \
  --pgdata /var/lib/neon/compute16/pgdata \
  --connstr postgresql://cloud_admin@127.0.0.1:5432/postgres \
  --pgbin /opt/neon/kernel/pg_install/v16/bin/postgres \
  --compute-id compute16 --config /etc/neon/compute16.json \
  --external-http-port 3080 --internal-http-port 3081
```

ECS8 替换 v16→v17、compute16→compute17。两台分别使用 5432 不冲突。不要给业务 PG 手工执行普通 initdb 后绕过 compute_ctl 启动。

## 9. 尚需补齐的交付项

完整多机自动化需要：节点清单读取、原生运行依赖安装、配置及 systemd 生成、私钥/JWKS 生成分发、节点注册和幂等初始化、compute spec 生成与通知更新、共享持久层方案和验收、真实 ECS 启停/迁移测试报告。本文没有把这些尚未完成的内容标记为已支持。
