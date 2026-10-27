# Neon 完整文件夹 ZIP 交付包

下载页面：https://github.com/DDDDDDDyunhua/neon-test-delivery/releases/tag/full-zip-20261027

本包直接压缩桌面的“Neon内核交付包-20261027”整个文件夹，保留全部 59,439 个文件、空目录、完整编译产物、源码、部署脚本和文档。没有裁剪编译结果。

GitHub 单个附件必须小于 2 GiB，因此完整 ZIP 按顺序分卷。请下载下面所有分卷到同一个文件夹，不要只下载第一个。

- `Neon-full-delivery-20261027.zip.001`
- `Neon-full-delivery-20261027.zip.002`
- `Neon-full-delivery-20261027.zip.003`

Windows：使用 7-Zip 打开 `Neon-full-delivery-20261027.zip.001` 并解压，其他分卷放在同一目录即可。或者先在命令提示符执行下面的合并命令，再解压生成的 ZIP：

```bat
copy /b Neon-full-delivery-20261027.zip.001+Neon-full-delivery-20261027.zip.002+Neon-full-delivery-20261027.zip.003 Neon-full-delivery-20261027.zip
```

Linux：

```bash
cat Neon-full-delivery-20261027.zip.[0-9][0-9][0-9] > Neon-full-delivery-20261027.zip
unzip Neon-full-delivery-20261027.zip
python3 "Neon内核交付包-20261027/restore-linux-metadata.py"
```

解压后的根目录包含 `kernel/`、`source/`、`deploy/`、`docs/`、`README.md` 和 Linux 文件权限/链接恢复工具。部署步骤见文件夹内 README 与 docs。

请下载本发布附件中的完整 ZIP 分卷；页面自动生成的 Source code (zip) 只包含仓库说明页。
