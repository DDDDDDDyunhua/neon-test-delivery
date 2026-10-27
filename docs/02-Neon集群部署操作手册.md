# Neon 集群测试部署：全新 ECS 操作手册

配套版本：20261027。先完成《01-Neon集群环境与交付要求.md》。下文 Linux 命令默认以 root 执行；只用于全新目录，不覆盖已有集群。部署结果为 11 个容器、PG16/PG17 两个独立实例、3 个 safekeeper、2 个 pageserver，持久化到本机磁盘。

## 1. 将目录复制到 ECS

从 Windows 用 SCP 递归复制整个 Neon内核交付包-20261027 目录到新 ECS，例如 /root/。无需压缩。在 ECS 执行：

```bash
cd /root/Neon内核交付包-20261027
python3 restore-linux-metadata.py
```

恢复 Linux 权限与链接的说明见根目录 README。

## 2. 复制运行文件到固定目录

以 root 执行：

```bash
test ! -e /opt/neon-cluster || { echo '已有安装目录，请停止并检查'; exit 1; }
mkdir -p /opt/neon-cluster
cp -a deploy/docker/. /opt/neon-cluster/
cp -a kernel /opt/neon-cluster/kernel
cd /opt/neon-cluster
```

此时 configs、compose.json、脚本、runtime-rootfs、runtime-locale 和 kernel 均为普通展开目录/文件。不要复制其他环境的 data、secrets 或 cluster-state。

## 3. 准备数据目录和认证文件

```bash
cd /opt/neon-cluster
python3 prepare.py
ls -ld data data/ps1 data/shared secrets configs
ls -l secrets/compute-jwt.pem configs/jwks.json
```

脚本创建 UID/GID 1000:1000 的数据目录、RSA JWT 私钥及匹配的 JWKS。它检测到已有 `data` 或 `secrets` 就拒绝运行。中途失败时先检查报错和目录，不能直接删除数据重试。私钥不应发给其他测试环境。

## 4. 导入运行环境并封装内核镜像

```bash
cd /opt/neon-cluster
tar -C runtime-rootfs -cf - . | docker import - neon-runtime-centos8:20261026
cat > .dockerignore <<'EOF'
*
!Dockerfile
!kernel
!kernel/**
!runtime-locale
!runtime-locale/**
EOF
docker build --network=none --pull=false -t neon-kernel:20261026 .
docker image inspect neon-kernel:20261026 --format '{{.Id}}'
```

基础镜像来自已展开的本地 rootfs 目录导入，构建上下文只包含 Dockerfile、内核和 locale，不包含 secrets 或数据。本步骤不下载源码、不运行 Cargo，也不重新编译 PG。

已验证的 Docker 26 环境也可使用下面命令选择旧构建器；较新 Docker 可能已经不提供该构建器，因此先执行上面的标准命令：

```bash
DOCKER_BUILDKIT=0 docker build --network=none --pull=false -t neon-kernel:20261026 .
```

如果构建器仍尝试拉取基础镜像，先检查 `docker images` 和 Dockerfile 的 FROM 标签是否一致；使用远程或 docker-container buildx builder 时，它可能无法直接读取本地 Docker image store，应切换到本机默认 builder 后重试。

## 5. 检查并注册 pageserver 专用 runtime

```bash
cd /opt/neon-cluster
ldd ./runc-newseccomp
./runc-newseccomp --version
python3 setup-runtime.py
docker info --format '{{json .Runtimes}}'
```

`ldd` 不应有 `not found`；版本输出应显示 libseccomp 2.5.5。脚本备份并合并 `/etc/docker/daemon.json`，运行 `dockerd --validate`，然后 reload Docker；若系统不支持 reload，需要管理员安排 Docker 重启后再继续。不要直接覆盖已有 daemon.json。

执行与 pageserver 同等安全限制的 syscall 探测：

```bash
docker run --rm --network none --runtime neon-runc \
  --cap-drop ALL --security-opt no-new-privileges:true \
  --entrypoint /usr/bin/python3 neon-kernel:20261026 -c \
  'import ctypes,sys; c=ctypes.CDLL(None,use_errno=True); r=c.syscall(436,100000,100001,0); e=ctypes.get_errno(); print("close_range result=",r,"errno=",e); sys.exit(0 if r==0 else 1)'
```

本命令针对本交付的 Linux amd64。必须得到 `result=0 errno=0`（输出空格可能不同）。EPERM 表示 runtime/seccomp 阻止调用；ENOSYS 表示宿主机未实现 syscall，应调整宿主机内核。不能通过关闭 seccomp 来替代验收。

若新系统无法加载提供的 runc，先停止此步骤并提交 `ldd` 和版本输出。现代宿主机也可以在默认 runtime 下执行同一探测（去掉 `--runtime neon-runc`）；若通过，可将 Compose 中 ps1/ps2 的 `runtime` 字段去掉并重新验证。该替代路径未在原 EL8 机器通过，原环境需要专用 runtime。

## 6. 启动控制面和存储节点

```bash
cd /opt/neon-cluster
./clusterctl config --quiet
./clusterctl up -d broker control-db compute-hook controller ps1 ps2 sk1 sk2 sk3
./clusterctl ps
curl -fsS http://127.0.0.1:2234/ready
```

此时不要手动启动 compute。先让 pageserver 容器启动，保证 controller 注册时 `ps1/ps2` 的容器 DNS 已存在。controller 依赖 control-db 和 compute-hook 健康，pageserver 只依赖 controller 已启动，以免初始化前形成健康检查等待环。

若尚未就绪，查看：

```bash
./clusterctl logs --tail=100 control-db controller compute-hook ps1 ps2
```

## 7. 初始化租户并启动两个计算节点

```bash
cd /opt/neon-cluster
python3 bootstrap.py 2>&1 | tee bootstrap.log
./clusterctl ps
cat cluster-state.json
```

脚本注册 2 个 pageserver 和 3 个 safekeeper，随机生成两个 tenant/timeline，分别用 PG16、PG17 初始化，配置一个主 pageserver 和一个 secondary，生成 compute16/17.json 并启动计算节点。成功末尾输出 `COMPUTES_STARTED`。启动不等于 SQL 已就绪，继续下一步验收。

`cluster-state.json` 是本环境的租户身份记录，必须保留。`bootstrap.py` 是初次部署入口；已有集群日常启动使用 `./clusterctl up -d`，不要反复用初始化脚本刷新运行配置，尤其不要在租户迁移后盲目重跑。

## 8. SQL 验收

默认测试账号：用户 `cloud_admin`，密码 `cloud_admin`，数据库 `postgres`。在容器中使用同一内核包里的 psql，不依赖宿主机 PG 安装：

```bash
cd /opt/neon-cluster
for v in 16 17; do
  ./clusterctl exec -T -e PGPASSWORD=cloud_admin compute$v \
    /opt/neon-kernel/pg_install/v$v/bin/psql \
    -X -v ON_ERROR_STOP=1 -h 127.0.0.1 -p 5432 -U cloud_admin -d postgres <<'SQL'
SELECT version();
CREATE SCHEMA IF NOT EXISTS acceptance;
CREATE TABLE IF NOT EXISTS acceptance.smoke(id integer PRIMARY KEY, value text);
INSERT INTO acceptance.smoke VALUES (1,'fresh-install-ok')
  ON CONFLICT(id) DO UPDATE SET value=excluded.value;
SELECT * FROM acceptance.smoke;
SHOW neon.tenant_id;
SHOW neon.timeline_id;
SQL
done
```

两次都应读出 `fresh-install-ok`，版本分别为 PG16 和 PG17，租户 ID 不同。首次连接失败先等待初始化完成并检查 compute 日志，不能以 HTTP 状态代替 SQL 验收。

确认同一个内核镜像被所有组件使用：

```bash
./clusterctl ps -q | xargs docker inspect --format '{{.Name}} {{.Image}}'
```

应有 11 个容器且 Image ID 一致。新机器重新构建的 Image ID 不要求与打包机完全相同；内核文件 SHA256 必须匹配交付清单。

## 9. 停止一个 safekeeper 后验收多数派写入

仅在本测试集群执行，保持另外两个 safekeeper 正常：

```bash
cd /opt/neon-cluster
./clusterctl stop sk3
for v in 16 17; do
  ./clusterctl exec -T -e PGPASSWORD=cloud_admin compute$v \
    /opt/neon-kernel/pg_install/v$v/bin/psql \
    -X -v ON_ERROR_STOP=1 -h 127.0.0.1 -U cloud_admin -d postgres \
    -c "SET statement_timeout='30s'; INSERT INTO acceptance.smoke VALUES (2,'quorum-ok') ON CONFLICT(id) DO UPDATE SET value=excluded.value; SELECT * FROM acceptance.smoke ORDER BY id;"
done
./clusterctl start sk3
./clusterctl ps
```

两实例均应提交成功并读出第二行。任何 SQL 失败也要先恢复 sk3，再排查日志。

## 10. 全组件停止后再启动

```bash
cd /opt/neon-cluster
./clusterctl stop
./clusterctl up -d
./clusterctl ps
```

等两个 compute 恢复就绪后，在两个版本分别执行：

```bash
for v in 16 17; do
  ./clusterctl exec -T -e PGPASSWORD=cloud_admin compute$v \
    /opt/neon-kernel/pg_install/v$v/bin/psql \
    -X -v ON_ERROR_STOP=1 -h 127.0.0.1 -U cloud_admin -d postgres \
    -c 'SELECT * FROM acceptance.smoke ORDER BY id;'
done
```

应保留前面两行。此步骤同时覆盖曾出现的 redo/seccomp 问题。它验证容器全停再启动；宿主机 reboot 需要另行执行并记录，不能视为已经覆盖。

## 11. 从测试电脑连接

Windows PowerShell 建立 SSH 隧道并保持窗口打开：

```powershell
ssh -N -L 56432:127.0.0.1:56432 -L 57432:127.0.0.1:57432 root@<新ECS-IP>
```

数据库客户端填写 `127.0.0.1`，PG16 端口 56432 或 PG17 端口 57432，账号密码均为 `cloud_admin`，数据库 `postgres`。若本地端口已占用，可将 `-L` 冒号前第一个端口改为本机空闲端口，并在客户端使用该端口。

默认测试密码只用于本隔离环境。需要更换时应同步维护 compute spec 中的角色密码配置，避免仅执行 SQL 修改后又被后续配置更新覆盖。

## 12. 日常操作、目录和备份

```bash
cd /opt/neon-cluster
./clusterctl ps
./clusterctl logs --tail=100 compute16 ps1
./clusterctl stop          # 保留容器及本机数据
./clusterctl up -d         # 再次启动已有集群
```

数据目录含义：`data/control-db` 是 controller 元数据；`data/ps1/ps2` 是各 pageserver 工作目录；`data/sk1/sk2/sk3` 是 WAL；`data/shared` 是 LocalFs 持久层；`data/compute*` 是计算节点本地 PG 数据；`data/compute-hook` 保存通知。另需保留 `configs`、`secrets`、`cluster-state.json` 和实际内核版本信息。

测试环境做一致性目录备份时先停止全部组件，再将上述目录和配置作为同一批次保存，完成后启动。只备份 compute 目录不足以恢复整个 Neon 集群。删除安装目录或 `data/shared` 会破坏持久化数据；本手册不包含自动清库步骤。

## 13. 常见问题

| 现象 | 检查与处理 |
| --- | --- |
| ECS 无法下载 Git | 本流程不需要 Git；先确认两个交付包到位。安装依赖所需的软件源连接另行排查，出方向放行全部不代表 DNS、路由和远端服务均正常 |
| `libssl.so.1.1` / ICU 库找不到 | 是否直接在不匹配的宿主机执行内核；应使用配套运行镜像，检查文件是否完整 |
| `initdb` locale 失败 | runtime-locale 是否随包保留且 Dockerfile 已复制；不要只导入基础 rootfs 就直接启动 |
| 数据目录 Permission denied | 检查宿主机 UID/GID 1000:1000 及 SELinux 标签；不要改为 777 |
| `unknown or invalid runtime name: neon-runc` | runtime 注册未成功或 Docker 未加载新配置，回到第 5 节 |
| `seccomp: could not close files >= fd 3`、读取页面 EOF | 检查 close_range 探测、两个 pageserver 的 runtime 和 libseccomp 版本 |
| controller 一直不 ready | 看 control-db/compute-hook 状态、元数据库日志、节点名称 DNS；不要把 pageserver 依赖改为等待 controller healthy |
| compute 通知返回 423 | 初次创建时 compute 尚未启动可能暂时出现；持续出现应检查 compute 配置、JWT/JWKS、3080 管理接口和 hook 日志 |
| compute 等待 safekeeper/WAL | 至少 2 个 safekeeper 可用；检查 tenant/timeline、generation 和地址是否来自本次初始化 |
| 端口已占用 | 用 `ss -lntp` 找占用者；此版本脚本有固定端口，改端口时需同步 Compose 与 bootstrap 中的地址 |
| 容器被 OOM kill | `docker inspect` 查看 OOMKilled，检查宿主机可用内存和服务 mem_limit，再调整测试负载 |
| SQL 公网连不上 | 默认绑定回环地址，按第 11 节使用 SSH 隧道 |

## 14. 测试交付记录


当前配套脚本完成了语法检查，核心配置取自既有已验证集群；尚未在另一台全新 ECS 完整走通全部步骤。新 ECS 只有完成第 8～10 节并保留结果，才能记为该环境部署验收通过。
