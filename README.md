# Neon 内部测试交付

这是公开测试仓库。源码、部署脚本和文档可直接查看；完整编译产物在 [Release test-20261027](https://github.com/DDDDDDDyunhua/neon-test-delivery/releases/tag/test-20261027)。

## 下载完整交付目录

原始编译结果未裁剪、未 strip，包括完整 target、build、PG14～17 安装产物，以及 proxy、local_proxy、pg_sni_router 等全部 18 个 release 程序。Release 使用**未压缩 tar 分卷**，仅为满足 GitHub 单附件大小限制，不减少文件内容。

在 Linux 上以 root 操作为例，以下命令无需 GitHub 账号：

```bash
mkdir -p /root/neon-delivery-download
cd /root/neon-delivery-download
base=https://github.com/DDDDDDDyunhua/neon-test-delivery/releases/download/test-20261027
for n in {000..021}; do
  curl -fL --retry 3 -O "$base/neon-full-build.tar.part-$n"
done
for n in 000 001; do
  curl -fL --retry 3 -O "$base/neon-test-support.tar.part-$n"
done
curl -fL --retry 3 -O "$base/restore-delivery.sh"
bash restore-delivery.sh /root/Neon内核交付包-20261027
```

也可以在公开 Release 页面下载所有分卷和 restore-delivery.sh 到同一目录，然后运行还原脚本。需要足够磁盘空间容纳下载分卷及展开结果。不要只下载 GitHub 自动生成的 Source code ZIP，它不含编译产物。

还原后：

```text
Neon内核交付包-20261027/
  kernel/target/        原始 Rust 完整编译目录
  kernel/build/         原始 PostgreSQL 构建目录
  kernel/pg_install/    PG14、15、16、17 完整安装产物
  kernel/bin/           指向 target/release 的便捷入口
  source/              全部源码、固定 Git 依赖对象和构建记录
  deploy/              完整原生/Docker 配套（含运行文件）
  docs/                部署手册
```

kernel/bin 在 Linux 使用目录软链接指向完整 release 目录，避免重复下载同一批可执行文件。原始 target、build、pg_install 无条目删减。

## 部署入口

- 单机原生：docs/03-Neon单机原生部署操作手册.md。
- Docker 模拟集群：docs/01-Neon集群环境与交付要求.md、docs/02-Neon集群部署操作手册.md。
- 多台真实 ECS：docs/04-多ECS原生部署方案说明.md，目前为方案说明，自动化及实际八机验证尚未完成。

本仓库 deploy/docker 主要供查看配置，运行 rootfs、locale、专用 runtime 和完整恢复文件在 Release 支持分卷内；部署时以还原后的目录为准。

内核来自 CentOS 8 Linux amd64 构建，需匹配运行库。此处发布的是当前构建结果，没有额外编译全部 feature 组合。原始构建目录中的链接和配置可能引用 /opt/neon 与原工具链路径。

## 源码

source/neon 包含保留的 Neon 快照及 PG14～17 vendor 源码；没有 Neon 原主仓库历史或主提交 SHA。source/build-records 包含 Cargo.lock、PG 子模块版本及历史构建命令；不是完整离线构建 SDK。原源码中的版权与许可证文件保留。

仓库和 Release 均公开，测试人员无需加入仓库即可下载。
