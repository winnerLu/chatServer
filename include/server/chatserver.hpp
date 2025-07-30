#ifndef CHATSERVER_H
#define CHATSERVER_H

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
using namespace muduo;
using namespace muduo::net;

/**
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
            const string& nameArg); // 服务器的名字

    /**
     * @brief 启动聊天服务器
     * 
     * 此方法用于启动 `ChatServer` 类所管理的 `TcpServer` 实例。
     * 调用该方法后，服务器将开始监听指定的 IP 地址和端口，
     * 准备接受客户端的连接请求，并处理相应的连接和读写事件。
     */
    void start();

private:
    // 专门处理用户的连接创建和断开 epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn);

    // 专门处理用户的读写事件的回调函数
    void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp time);


private:
    TcpServer _server; // 组合的muduo库的TcpServer对象
    EventLoop *_loop; // 指向事件循环的指针，用于处理网络事件

};


#endif