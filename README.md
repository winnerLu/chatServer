# chatServer
C++ ChatServer
编译muduo_server单文件
g++ -std=c++11 -o muduo_server /home/lsc/devs/chatServer/testMuduo/muduo_server.cpp -I/usr/local/include -L/usr/local/lib -lmuduo_net -lmuduo_base -lpthread

使用telnet命令进行测试
telnet 127.0.0.1 8888

telnet 是一个用于远程登录和网络测试的命令行工具，它基于 Telnet 协议工作。Telnet 协议是一种应用层协议，允许用户通过网络连接到远程计算机，在远程主机上执行命令，就像直接在那台主机前操作一样。
基本语法：telnet [主机名或 IP 地址] [端口号]

## 从命令交互模式退出Telnet
当通过 Telnet 成功连接到远程服务器后，会进入命令交互模式。在此模式下，可以与远程服务器进行命令交互。若要退出，需要先进入 Telnet 内部命令模式，具体步骤如下：

1. 进入 Telnet 内部命令模式：在命令交互模式下，按下 Ctrl + ] 组合键，此时会进入 Telnet 内部命令模式，终端会显示类似 telnet> 的提示符。
2. 输入退出命令：在 telnet> 提示符后输入 quit 命令，然后按下回车键，即可退出 Telnet 连接。

可以在命令交互模式使用？或者help命令查看所有命令

## 编译
- 使用Cmake Tools插件进行编译，会在项目根目录下生成build目录，编译后的可执行文件会在build目录下。
- 编译命令：cmake --build build
- 使用cmake命令进行编译，cmake . 会在当前目录下生成build目录，编译后的可执行文件会在build目录下。
- 清除cmake编译：cmake --build build --target clean

## WSL安装MySQL

- sudo apt install mysql-server -y
- 启动MySQL sudo /etc/init.d/mysql start  或者sudo service mysql start
- 首次登陆使用sudo mysql
- 设置密码：
- ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'Aa123456';
- FLUSH PRIVILEGES;
- 关闭mysql服务：sudo service mysql stop
- 之后登陆使用 mysql -u root -p

- 查看MySQL默认的字符编码：show variables like "char%"
- 使用sudo netstat -tanp查看MySQL服务是否启动，默认监听3306端口

- 创建数据库CREATE DATABASE new_db_name
  DEFAULT CHARACTER SET utf8mb4
  COLLATE utf8mb4_general_ci;
