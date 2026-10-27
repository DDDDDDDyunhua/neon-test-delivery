# Neon 集群测试部署：环境与交付要求

适用交付：20261026 Linux amd64 内核包；配套脚本版本：20261027。阅读顺序：先完成本文检查，再执行《02-Neon集群部署操作手册.md》。本文面向拿到全新 ECS 的测试人员，不要求接触源码或原部署机器。

## 1. 部署目标

在一台 ECS 上用 Docker 网络、进程和目录隔离模拟多个节点。11 个容器使用同一个内核镜像：

| 角色 | 数量 | 用途 |
| --- | ---: | --- |
| storage_broker | 1 | 节点发现与状态交换 |
| storage_controller | 1 | 节点管理、租户放置和迁移 |
| control-db | 1 | controller 的 PostgreSQL 17 元数据库 |
| compute-hook | 1 | 将 controller 通知转换为 compute 配置更新 |
| pageserver | 2 | 页面存储，租户采用一个主节点和一个 secondary 的放置策略 |
| safekeeper | 3 | WAL 存储，按多数派提交 |
| compute | 2 | 分别运行 PG16、PG17，使用不同租户与 timeline |

两个 pageserver 共享宿主机 `data/shared` 作为 LocalFs 后端。此方案没有接入 OBS/S3；LocalFs 也不是独立的高可用对象存储。PG16 和 PG17 不是互为主备。容器隔离可用于组件功能、迁移和进程故障测试；整台 ECS 或磁盘故障仍会影响整个集群。

## 2. 本次测试包内容

kernel/ 保存完整编译结果：target、build、PG14～17 安装目录；bin/ 为全部 release 程序的便捷副本。deploy/docker/ 是已展开的 Docker 配置和运行环境，deploy/single/ 是原生单机脚本，source/ 是源码。

Windows 复制到 Linux 后先执行根目录的 restore-linux-metadata.py，恢复权限与链接，再继续部署。初始化时生成新租户和密钥。

## 3. ECS 规格与系统

| 项目 | 本方案要求或建议 |
| --- | --- |
| CPU 架构 | x86_64 / amd64；ARM ECS 不能直接使用本批内核 |
| CPU | 建议 8 vCPU 起 |
| 内存 | 建议 16 GiB 起；压力测试需按负载增加 |
| 磁盘 | 建议至少 100 GiB 可用 SSD 空间；日志、WAL、数据增长需另计 |
| 权限 | root 或可 sudo；需要创建目录、配置 Docker runtime |
| 文件系统 | 支持普通 Linux 权限与持久化写入的 ext4/XFS 等；避免临时盘承载唯一数据 |
| 安装路径 | 本批配套固定为 `/opt/neon-cluster`；不要随意改名，runc 内嵌库路径也使用此目录 |

已实际验证的宿主机是 CentOS Linux 8、8 核 16 GiB、内核 `4.18.0-348.7.1.el8_5.x86_64`，Docker 26.1.3、Compose 2.27.0。CentOS 8 已结束生命周期，不建议为新采购机器继续选择它。

新 ECS 可选 Ubuntu 22.04/24.04 amd64；这是建议的适配目标，**尚未在全新 Ubuntu ECS 上完成本文整套验证**。必须通过运行库、runtime 和 syscall 检查，再进行部署验收。不要把“镜像能构建”当成宿主机兼容性已经通过。

## 4. 软件依赖

宿主机需要：Docker Engine、Docker Compose v2、Python 3、OpenSSL、tar、gzip、curl、基础 shell 和 systemd。Python 只用标准库，不需要 pip install。Docker API 和 Compose 必须能正常使用。

不需要在测试机器上安装 Rust、Cargo、C/C++ 编译器、protoc，也不需要下载 Neon Git 仓库。此处 `docker build` 只是封装已编译产物，不会重新编译 Neon。

容器所需 glibc、OpenSSL、ICU、Python、CA 和 locale 由配套包的运行环境提供。不要直接把这些 CentOS 运行库覆盖到宿主机 `/usr/lib*`。

Ubuntu 安装示例（以 root 执行；Docker 仓库无法访问时使用组织批准的镜像源或离线安装包）：

```bash
apt-get update
apt-get install -y ca-certificates curl python3 openssl tar gzip
install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
chmod a+r /etc/apt/keyrings/docker.asc
. /etc/os-release
cat > /etc/apt/sources.list.d/docker.sources <<EOF
Types: deb
URIs: https://download.docker.com/linux/ubuntu
Suites: ${UBUNTU_CODENAME:-$VERSION_CODENAME}
Components: stable
Architectures: $(dpkg --print-architecture)
Signed-By: /etc/apt/keyrings/docker.asc
EOF
apt-get update
apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
systemctl enable --now docker
docker version
docker compose version
```

安装方法参考 [Docker 官方 Ubuntu 安装说明](https://docs.docker.com/engine/install/ubuntu/)。仓库最新版不等于本方案已验证版本，测试应记录实际版本。已有 Docker 的机器先检查现状，避免直接执行上述仓库覆盖步骤。

对 EL8 系统，先保证系统仓库可用，再安装上述对应软件。已验证机器曾使用华为云 Docker CE 镜像源，EPEL 不可用时临时禁用相关仓库；这些属于该机器的仓库修复，不是每台全新 ECS 都必须照做的步骤。

## 5. 网络与安全组

安装阶段需要访问系统和 Docker 软件仓库；取得完整未压缩交付目录后，构建内核镜像、初始化集群不需要访问 GitHub、Docker Hub 或 OBS。

| 接口 | 宿主机绑定 | 用途 |
| --- | --- | --- |
| SSH | ECS 的 22/tcp（或实际 SSH 端口） | 登录、上传、SSH 隧道 |
| PG16 | 127.0.0.1:56432 | 测试 SQL |
| PG17 | 127.0.0.1:57432 | 测试 SQL |
| controller | 127.0.0.1:2234 | 管理与 readiness |
| pageserver HTTP | 127.0.0.1:21981、21982 | 状态与排障 |
| safekeeper HTTP | 127.0.0.1:27671～27673 | 状态与排障 |

容器通过私有 bridge 网络互通，内部使用 broker 50051、control-db 5432、pageserver 6400/9898/51051、safekeeper 5454/7676、compute 管理 3080/3081 等端口。无需在 ECS 安全组逐个开放。只开放安全组不能让绑定在 127.0.0.1 的 SQL 服务变成公网可达；远程测试使用 SSH 隧道。

控制面和内部存储链路采用测试用 trust/dev 配置，SQL 初始密码也为测试默认值。本交付用于隔离测试环境，不能直接作为公网生产服务配置。

## 6. 内核与 seccomp 兼容性

pageserver 的 WAL redo 子进程依赖 `close_range`。旧 EL8 上曾出现：宿主机实现了 syscall，但旧版 libseccomp 不认识它，容器内返回 EPERM，最终报 `seccomp: could not close files >= fd 3`。仅启动 HTTP 健康检查不一定暴露问题，完整重启后读写也要验收。

本批配套提供独立 `neon-runc`，其 runc 使用 libseccomp 2.5.5，仅供两个 pageserver 使用，不替换系统 runc，不关闭容器默认 seccomp。操作手册包含注册和探测步骤。该二进制来自已验证 EL8 环境，其他发行版仍须通过 `ldd`、`runc --version` 和实际 syscall 探测。探测不通过时不要继续初始化。

## 7. 部署前检查清单

```bash
uname -m
uname -r
cat /etc/os-release
nproc
free -h
df -h /opt /var/lib/docker
docker info
docker compose version
python3 --version
openssl version
ss -lnt
```

确认：amd64；空间和内存足够；Docker 正常；本文宿主机端口未占用；`/opt/neon-cluster` 不存在旧数据。容器以 UID/GID 1000:1000 写挂载目录，由初始化脚本创建权限。

SELinux 为 Enforcing 时，默认挂载标签可能阻止容器写入。应按发行版规范为这些专用目录配置容器访问标签，或在 Compose 挂载处设置正确的共享标签；不要用 `chmod 777` 或关闭整个宿主机防护来掩盖问题。当前配套未在 SELinux Enforcing 模式完成适配验收。

## 8. 交付与验收边界

本批内核来自同一套 release 构建，PG16.9 / PG17.5。它不代表所有 feature 组合或源码测试目标都已编译。更换内核版本、架构、glibc 基线或 PG 主版本时，必须重新匹配运行环境和配置 API，不能沿用本批 SHA256。

现有 ECS 的同构集群已通过 PG16/17 读写、单 safekeeper 停止后写入、PG16 租户迁移和全组件停止再启动的数据读取。新增交付脚本做过语法检查；本两份手册仍需由测试在目标新 ECS 上执行验收，不能把既有集群的结果当作新机器验收记录。
