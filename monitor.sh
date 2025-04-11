#!/bin/bash

# 编译C程序
echo "正在编译C程序..."
gcc src/resource_collector.c -o src/collector

# 设置定时任务（每5分钟采集一次）
echo "设置定时任务..."
(crontab -l 2>/dev/null; echo "*/5 * * * * $(pwd)/src/collector") | crontab -

# 启动Web服务器（端口8000）
echo "启动Web服务器..."
python3 -m http.server 8000 --directory web/ &

echo "✅ 部署完成！访问地址：http://localhost:8000/dashboard.html"
