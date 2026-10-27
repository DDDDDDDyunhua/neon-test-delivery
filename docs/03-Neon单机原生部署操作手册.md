# Neon 单机原生部署操作手册（内核包交付）

版本：20261027。目标：全新 Linux ECS + 已编译内核包，直接启动进程，不使用 Docker，不下载源码，不接 OBS/S3。默认业务数据库 PG16，可选改为 PG17。

本文依据当前内核包和既有 ECS 的单机部署记录整理。原源码目录布局的单机部署已验证；本文改为交付包布局，尚未在另一台全新 ECS 完成全流程复测。

## 1. 单机版会启动什么

单机版不是只启动一个 postgres，仍有独立进程，通过回环地址通信：

```text
一台 ECS
  neon_local：初始化、协调和管理本机组件
  storage_controller + 内部元数据库
  storage_broker
  pageserver × 1
  safekeeper × 1
  endpoint_storage
  compute_ctl + Neon PostgreSQL 16（业务入口）
  本机磁盘：全部组件数据和 LocalFs 持久层
```

使用 `neon_local` 统一启动，无需手动逐个注册节点和编辑 compute spec。它是开发/测试控制工具，本方案不具备主机故障冗余，不作为生产高可用部署。

## 2. 环境和交付物

建议 8 vCPU、16 GiB 内存、至少 50 GiB 可用磁盘；压力测试另行扩容。要求 amd64/x86_64、普通持久化 Linux 文件系统、root 安装权限、systemd 和普通运行用户。

需要交付：

```text
kernel/（完整 target、build、pg_install，以及 bin 便捷入口）
本操作手册
匹配目标发行版的运行依赖或可用软件仓库
```

内核包含完整 target、build、PG14～17 安装目录和 bin 便捷入口。PG17 不要删除，本地管理工具需要用它启动 controller 元数据库。这里不需要 Docker 集群配套包，也不要执行其 `prepare.py`、`bootstrap.py` 或 `setup-runtime.py`。

已验证宿主机为 CentOS Linux 8 x86_64、内核 4.18.0-348.7.1.el8_5；内核包来自该系统。CentOS 8 已结束生命周期。选择其他系统时先核对 ABI，不能把本包视为任意 Linux 通用包。EL8 兼容发行版可作为适配目标，但尚未逐一验收；Ubuntu 新版本通常不直接提供此包需要的 OpenSSL 1.1、ICU 60，需要另行提供匹配发行版构建或经过验证的运行环境。

### 2.1 运行依赖

本包需要 glibc、libgcc、libstdc++、OpenSSL 1.1、ICU 60、zlib、readline、libcurl、libseccomp、CA 和 UTF-8 locale 等。工具需要 bash、tar、gzip、curl、Python3、runuser、systemd；不需要 Rust、Cargo、protoc 或编译工具链。

EL8 软件包安装示例（先保证软件仓库可用）：

```bash
dnf install -y \
  glibc libgcc libstdc++ openssl-libs libicu zlib readline \
  libcurl libseccomp ca-certificates glibc-langpack-en \
  bash tar gzip coreutils curl python3 util-linux shadow-utils
```

不同发行版包名/版本可能不同。以解压后的 `ldd` 和 locale 检查为准；不要只因 dnf 成功就认为依赖齐全。不要把 Docker 配套 rootfs 中的库覆盖到宿主机 `/usr/lib*`。

## 3. 复制文件到 ECS

先将完整交付目录递归复制到新 ECS，例如 /root/Neon内核交付包-20261027。以下以 root 执行：

```bash
cd /root/Neon内核交付包-20261027
python3 restore-linux-metadata.py
test ! -e /opt/neon-single || { echo '已有安装目录，请停止并检查'; exit 1; }
mkdir -p /opt/neon-single
cp -a kernel /opt/neon-single/kernel
id neon >/dev/null 2>&1 || useradd -m -s /bin/bash neon
chown neon:neon /opt/neon-single
```

本节为手工部署路径。如果已经按 deploy/single/README 使用 install.sh 安装，不要重复第 3、5、6 节写文件步骤，继续检查依赖并首次初始化。

内核位于 /opt/neon-single/kernel，实例数据在初始化后生成的 /opt/neon-single/.neon。不要以 root 运行 PostgreSQL。

## 4. 检查二进制、扩展和 locale

```bash
export LD_LIBRARY_PATH=/opt/neon-single/kernel/pg_install/v17/lib:/opt/neon-single/kernel/pg_install/v16/lib
ldd /opt/neon-single/kernel/bin/pageserver
ldd /opt/neon-single/kernel/bin/neon_local
ldd /opt/neon-single/kernel/bin/storage_controller
ldd /opt/neon-single/kernel/bin/compute_ctl
ldd /opt/neon-single/kernel/pg_install/v16/bin/postgres
ldd /opt/neon-single/kernel/pg_install/v17/bin/postgres
ldd /opt/neon-single/kernel/pg_install/v16/lib/neon.so
ldd /opt/neon-single/kernel/pg_install/v17/lib/neon.so
LC_ALL=C.UTF-8 locale charmap
```

各 `ldd` 不应有 `not found`；locale 应正常输出 UTF-8 编码，不应提示无法设置 locale。还需检查其他将要运行的 bin、PG 客户端和 Neon 扩展依赖；上面列的是重点项，不是完整 ABI 扫描。

如果 `C.UTF-8` 不可用，应先安装适合该发行版的 locale 数据并验证。不要直接假定仅设置环境变量就创建了 locale。

检查可用端口：

```bash
ss -lntp
```

本方案默认使用：1234、1235、5454、7676、9898、9993、50051、51051、64000、55432，以及 compute 管理接口通常使用的 55433/55434。已有源码单机实例正在使用这些端口时，不应在同一台机器直接照抄启动；本文面向全新 ECS。

## 5. 创建本机初始化配置

以 root 写入：

```bash
cat > /opt/neon-single/init.toml <<'EOF'
pg_distrib_dir = "/opt/neon-single/kernel/pg_install"
neon_distrib_dir = "/opt/neon-single/kernel/bin"
default_tenant_id = "00000000000000000000000000000000"
control_plane_api = "http://127.0.0.1:1234/upcall/v1/"
generate_local_ssl_certs = false

[broker]
listen_addr = "127.0.0.1:50051"

[endpoint_storage]
listen_addr = "127.0.0.1:9993"

[[pageservers]]
id = 1
listen_pg_addr = "127.0.0.1:64000"
listen_http_addr = "127.0.0.1:9898"
listen_grpc_addr = "127.0.0.1:51051"
pg_auth_type = "Trust"
http_auth_type = "Trust"
grpc_auth_type = "Trust"
no_sync = false
virtual_file_io_engine = "std-fs"

[[safekeepers]]
id = 1
pg_port = 5454
http_port = 7676
sync = true
listen_addr = "127.0.0.1"
EOF
chmod 644 /opt/neon-single/init.toml
```

这里 `default_tenant_id` 是初始化配置占位值，后面的 `tenant create --set-default` 会设定新创建的默认租户；不要复制其他环境的真实 tenant/timeline 身份。

## 6. 安装 neon-single 管理命令

以下包装命令固定工作目录、运行用户、库路径和实例目录，不依赖源码或 Cargo：

```bash
cat > /usr/local/bin/neon-single <<'EOF'
#!/bin/bash
set -euo pipefail
if [ "$(id -u)" -eq 0 ]; then
  exec runuser -u neon -- /usr/local/bin/neon-single "$@"
fi
if [ "$(id -un)" != neon ]; then
  echo '请以 root 或 neon 用户执行' >&2
  exit 1
fi
export NEON_REPO_DIR=/opt/neon-single/.neon
export PATH=/opt/neon-single/kernel/bin:/opt/neon-single/kernel/pg_install/v17/bin:/usr/local/bin:/usr/bin:/bin
export LD_LIBRARY_PATH=/opt/neon-single/kernel/pg_install/v17/lib:/opt/neon-single/kernel/pg_install/v16/lib
cd /opt/neon-single
exec /opt/neon-single/kernel/bin/neon_local "$@"
EOF
chmod 755 /usr/local/bin/neon-single
neon-single --help
```

## 7. 首次初始化和启动存储组件

**本节初始化只运行一次。** 检测到 `.neon` 已存在时先检查，不能覆盖。

```bash
test ! -e /opt/neon-single/.neon || { echo '已有实例目录，禁止重复初始化'; exit 1; }
neon-single init --config /opt/neon-single/init.toml
neon-single start --start-timeout 60s
```

工具负责启动本机控制器及元数据库、broker、pageserver、safekeeper 和 endpoint_storage，协调注册与就绪检查。预期出现 `Neon started and passed status check`；失败应先检查各组件日志，不要继续创建 endpoint。

生成后的 pageserver 配置应包含本地持久层，例如：

```toml
remote_storage = { local_path = '../local_fs_remote_storage/pageserver' }
```

检查实际生成配置：

```bash
rg 'remote_storage' /opt/neon-single/.neon/pageserver_1/pageserver.toml
```

没有安装 rg 时使用 `grep remote_storage`。这里不是访问远程对象存储；相对目录由本地工具按其工作布局解析，不要随意修改生成的目录结构。

## 8. 创建 PG16 业务实例

```bash
neon-single tenant create --set-default --pg-version 16
neon-single endpoint create main --pg-version 16 --pg-port 55432
neon-single endpoint start main
neon-single endpoint list
```

本流程将创建真实的新 tenant/timeline，生成计算节点配置，再由 compute_ctl 启动配套 PostgreSQL。**不要另行给业务 PG 执行普通 initdb，也不要绕开 compute_ctl 手工启动 postgres。**

首次业务实例启动前，确保云安全组未开放 compute 管理端口。检查监听：

```bash
ss -lntp
```

已验证原实例的 SQL 为 `127.0.0.1:55432`，compute 管理接口为 wildcard 55433/55434。新部署以实际输出为准：SQL 应限制为本机，管理接口只允许本机访问。可使用现有主机防火墙规则或云安全组限制，IPv4/IPv6 都要覆盖；不要为测试直接放开全部入方向端口。

### 可选：首次就使用 PG17

若只需要 PG17，在全新实例第 8 节改为以下三条，不要先运行 PG16 那组：

```bash
neon-single tenant create --set-default --pg-version 17
neon-single endpoint create main --pg-version 17 --pg-port 55432
neon-single endpoint start main
```

随后验收使用 v17 的 psql。若要同机同时运行两个 PG 版本，应分别创建租户、显式关联 endpoint 并分配不同端口，属于扩展方案，不要把同一个已有 PG16 timeline 直接用 PG17 打开。

## 9. SQL 读写验收

PG16 默认连接：用户 `cloud_admin`，数据库 `postgres`，本机端口 55432。本地开发配置为 trust，不要求填写 Docker 集群方案中的 `cloud_admin` 密码。

```bash
runuser -u neon -- env \
  LD_LIBRARY_PATH=/opt/neon-single/kernel/pg_install/v16/lib \
  /opt/neon-single/kernel/pg_install/v16/bin/psql \
  -X -v ON_ERROR_STOP=1 -h 127.0.0.1 -p 55432 \
  -U cloud_admin -d postgres <<'SQL'
SELECT version();
CREATE TABLE public.neon_single_acceptance (
    id integer PRIMARY KEY,
    note text NOT NULL
);
INSERT INTO public.neon_single_acceptance VALUES (1,'single-node-persistence-ok');
SELECT * FROM public.neon_single_acceptance;
SHOW synchronous_commit;
CHECKPOINT;
SQL
```

预期版本为本批 PG16.9；插入查询成功；`synchronous_commit=on`。重复验收前检查表是否已存在，保留原验收数据，不要盲目重新创建。

## 10. 交给 systemd 管理

先停止第 7～8 节手动启动的整套实例，再由 systemd 接管：

```bash
neon-single stop
cat > /opt/neon-single/service.sh <<'EOF'
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
EOF
chmod 755 /opt/neon-single/service.sh

cat > /etc/systemd/system/neon-single.service <<'EOF'
[Unit]
Description=Neon single-host native test environment
After=network.target

[Service]
Type=oneshot
RemainAfterExit=yes
User=neon
Group=neon
WorkingDirectory=/opt/neon-single
ExecStart=/opt/neon-single/service.sh start
ExecStop=/opt/neon-single/service.sh stop
TimeoutStartSec=180
TimeoutStopSec=120
LimitNOFILE=65536
KillMode=control-group

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable --now neon-single.service
systemctl status neon-single.service --no-pager
neon-single endpoint list
```

`active (exited)` 是 oneshot 管理单元的正常状态，不是持续监控所有子进程的健康状态。还需用 SQL、组件日志和端口确认服务正常。本单元不会在任一组件异常退出后自动逐个恢复它；测试人员应监控并按故障原因处理。

## 11. 全套重启后验证持久化

```bash
systemctl restart neon-single.service
runuser -u neon -- env \
  LD_LIBRARY_PATH=/opt/neon-single/kernel/pg_install/v16/lib \
  /opt/neon-single/kernel/pg_install/v16/bin/psql \
  -X -v ON_ERROR_STOP=1 -h 127.0.0.1 -p 55432 \
  -U cloud_admin -d postgres \
  -c 'SELECT * FROM public.neon_single_acceptance;'
```

应仍读出 `1 | single-node-persistence-ok`。这验证正常停止再启动的数据保留，不是断电、磁盘故障或高可用测试。实际宿主机重启验收需另行执行并记录。

## 12. 从测试电脑访问

在电脑建立 SSH 隧道，保持窗口打开：

```bash
ssh -N -L 55432:127.0.0.1:55432 root@<新ECS-IP>
```

数据库客户端连接本机 `127.0.0.1:55432`、用户 `cloud_admin`、数据库 `postgres`。无需对公网开放 SQL 55432 或内部管理端口。

## 13. 日常操作和故障排查

接管后统一使用 systemd 整套启停：

```bash
systemctl start neon-single
systemctl stop neon-single
systemctl restart neon-single
systemctl status neon-single --no-pager
journalctl -u neon-single -n 100 --no-pager
neon-single endpoint list
find /opt/neon-single/.neon -type f -name '*.log'
```

| 问题 | 检查 |
| --- | --- |
| 缺少 libssl / ICU / 其他 .so | 运行包 ABI 是否匹配宿主机；LD_LIBRARY_PATH 和扩展依赖是否齐全 |
| initdb 拒绝 root | 是否通过 neon-single 包装命令以 neon 用户执行 |
| locale 错误 | 宿主机 C.UTF-8 是否可用，安装正确的 locale 数据 |
| controller 元数据库启动失败 | 是否保留了 pg_install/v17；1235 是否占用；查看内部数据库日志 |
| pageserver I/O 不兼容 | 是否使用 std-fs；本机内核及运行库是否满足需要 |
| close_range / seccomp 报错 | 先检查原生宿主机 syscall 和 libseccomp；Docker 专用 neon-runc 修复不适用于此原生进程方案 |
| 服务显示 active 但 SQL 不通 | oneshot 不等于实时健康，检查 endpoint、子进程、端口和日志 |
| 电脑连接失败 | SSH 隧道是否存活，客户端是否连本机端口，本机端口是否占用 |

## 14. 数据保护与验收记录


不要只备份业务 compute 的 pgdata；不要删除 local_fs_remote_storage；不要对已有实例重复 init；不要把旧实例目录作为通用内核包分发。

建议记录：系统与内核、运行库版本、初始化与启动输出、endpoint list、监听端口、SQL 读写结果、完整重启后的查询结果。本文对应交付布局尚待目标新 ECS 实测通过。

参考：[Neon 官方本地开发控制工具说明](https://github.com/neondatabase/neon/blob/main/control_plane/README.md)。在线 main 会变化，具体命令以本包 neon_local --help 为准。
