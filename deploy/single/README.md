# 单机原生部署（未压缩文件）

先阅读交付根目录 README 和 docs/03-Neon单机原生部署操作手册.md，安装匹配系统运行依赖。在目标 Linux 的交付目录执行 `python3 restore-linux-metadata.py` 后继续：

```bash
sudo bash deploy/single/install.sh "$PWD/kernel"
sudo bash deploy/single/precheck.sh
sudo neon-single init --config /opt/neon-single/init.toml
sudo neon-single start --start-timeout 60s
sudo neon-single tenant create --set-default --pg-version 16
sudo neon-single endpoint create main --pg-version 16 --pg-port 55432
sudo neon-single endpoint start main
```

完成 SQL 验收后，先 `sudo neon-single stop`，再 `sudo systemctl enable --now neon-single.service`，执行整套停启验收。不要重复手册中手工解压/写文件或 init 的步骤。

安装器接收已展开的 kernel 目录，固定安装 /opt/neon-single，拒绝覆盖已有环境，只安装文件，不自动初始化和启动，也不修改防火墙。新 ECS 全流程尚待实测。
