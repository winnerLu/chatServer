#include <muduo/base/CurrentThread.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <functional>
#include <iostream>
#include <string>

using namespace muduo;
using namespace muduo::net;

/*
 * @brief 聊天服务器类
 * 1. 负责维护服务器端的连接和通信
 * 2. 负责处理用户的连接创建和断开
 * 3. 负责处理用户的读写事件
 *
 * @note 开发步骤
 * 1. 组合TcpServer对象
 * 2. 创建 EventLoop 事件循环对象的指针
 * 3. 明确 TcpServer 构造函数需要什么参数，输出 ChatServer 类的构造函数
 * 4. 在当前服务器类的构造函数中，注册连接回调和消息回调
 * 5. 设置合适的线程数量，muduo库会自动分配I/O线程数和worker线程数
*/
class ChatServer
{
public:
    /**
     * @brief ChatServer 类的构造函数
     * 
     * 初始化聊天服务器，设置服务器的事件循环、监听地址和名称，
     * 并注册连接回调、消息回调，同时设置服务器线程数量。
     * 
     * @param loop 事件循环指针，用于处理网络事件
     * @param listenAddr 服务器监听的地址，包含 IP 地址和端口号
     * @param nameArg 服务器的名称，用于标识该服务器实例
     */
    ChatServer(EventLoop* loop, // 事件循环
            const InetAddress& listenAddr, // IP+Port
            const string& nameArg) // 服务器的名字
        :_server(loop, listenAddr, nameArg), _loop(loop) // 初始化 TcpServer 实例和事件循环指针
    {
        // 给服务器注册用户连接和断开回调，当有新连接建立或连接断开时，调用 onConnection 函数
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        // 给服务器注册用户读写事件回调，当接收到客户端消息时，调用 onMessage 函数
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端 EventLoop 的线程数量，总共 10 个线程，其中 1 个 IO 线程，9 个工作线程，muduo自动分配
        // 注意：在 WSL 环境下，可调用 Windows 系统可用的全部核心与线程
        _server.setThreadNum(10);
    }

    /**
     * @brief 启动聊天服务器
     * 
     * 此方法用于启动 `ChatServer` 类所管理的 `TcpServer` 实例。
     * 调用该方法后，服务器将开始监听指定的 IP 地址和端口，
     * 准备接受客户端的连接请求，并处理相应的连接和读写事件。
     */
    void start()
    {
        // 调用 TcpServer 实例的 start 方法，启动服务器监听
        _server.start();
    }

private:
    // 专门处理用户的连接创建和断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn) 
    {
        if (conn->connected()) {
            std::cout << "连接创建成功" << std::endl;
            // peerAddress 对端地址
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << std::endl;
        } else {
            std::cout << "连接断开成功" << std::endl;
            std::cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << std::endl;
            conn->shutdown(); // 关闭连接 close(fd)
            // _loop->quit(); // 退出事件循环，关闭服务器
        }
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp time) 
    {
        string buf = buffer->retrieveAllAsString();
        std::cout << "onMessage: " << buf << " 时间: " << time.toString() <<std::endl;
        conn->send(buf);
    }


private:
    TcpServer _server;
    EventLoop *_loop;

};

class chatClient 
{
public:


private:
    TcpClient _client;
    EventLoop *_loop;

    // 用户连接创建和断开回调
    std::function<void(const muduo::net::TcpConnectionPtr&)> _connectionCallback;

    // 用户读写事件回调
    std::function<void(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp)> _messageCallback;

};

int main()
{
    EventLoop loop;
    InetAddress addr("127.0.0.1", 8888);
    ChatServer server(&loop, addr, "chatServer");

    server.start();
    loop.loop(); // epoll_wait以阻塞方式等待新用户连接，已连接用户的读写事件等

    return 0;
}