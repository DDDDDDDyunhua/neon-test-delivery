# Docker 模拟集群（已展开）

本目录已直接展开 Compose、配置、脚本、runtime-rootfs、runtime-locale 及 scoped runc。内核位于交付根目录 kernel。

先在 Linux 完成权限和链接恢复。把本目录内容复制到 /opt/neon-cluster，再将交付根目录 kernel 作为 /opt/neon-cluster/kernel 复制过去。详见 docs/02-Neon集群部署操作手册.md。

原来的 `docker import runtime-rootfs.tar ...` 改为：

```bash
tar -C runtime-rootfs -cf - . | docker import - neon-runtime-centos8:20261026
```

这里是通过未压缩 tar 数据流向 Docker 导入文件系统，不产生交付压缩包。其他配置和初始化步骤不变。不要把运行 rootfs 的库覆盖到宿主机系统目录。
