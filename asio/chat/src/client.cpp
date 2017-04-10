/*************************************************************************
	> File Name: client.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月10日 星期一 09时46分59秒
 ************************************************************************/

#include "codec.h"
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/TcpClient.h>

#include <boost/noncopyable.hpp>

#include <cstdio>
#include <cstdint>
#include <iostream>
#include <functional>  //for _1, _2, _3

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

class ChatClient : boost::noncopyable
{
public:
    ChatClient(EventLoop* loop, const InetAddress& listenAddr)
    :loop_(loop), client_(loop, listenAddr, "ChatClient"), codec_(std::bind(&ChatClient::onStringMessage, this, _1, _2, _3))
    {
        client_.setConnectionCallback(std::bind(&ChatClient::onConnection, this, _1));
        client_.setMessageCallback(std::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
        client_.enableRetry();
    }

    void connect()
    {
        client_.connect();
    }

    void disconnect()
    {
        client_.disconnect();
    }

    void write(const StringPiece& message)
    {
        MutexLockGuard lock(mutex_);
        if (connection_)
        {
            codec_.send(get_pointer(connection_), message);
        }
    }

private:
    void onConnection(const TcpConnectionPtr& conn)
    {
        LOG_INFO << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");

        MutexLockGuard lock(mutex_);
        if (conn->connected())
        {
            connection_ = conn;
        }
        else
        {
            connection_.reset();
        }
    }

    void onStringMessage(const TcpConnectionPtr&, const string& message, Timestamp)
    {
        printf("<<< %s\n", message.c_str());
    }

    EventLoop* loop_;
    TcpClient client_;
    LengthHeaderCodec codec_;
    MutexLock mutex_;
    TcpConnectionPtr connection_;
};

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    if (argc > 2)
    {
        EventLoopThread loopThread;
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress serverAddr(argv[1], port);

        ChatClient client(loopThread.startLoop(), serverAddr);
        client.connect();
        std::string line;
        while (std::getline(std::cin, line))
        {
            client.write(line);
        }
        client.disconnect();
        CurrentThread::sleepUsec(1000 * 1000);
    }
    else
    {
        fprintf(stderr, "Usage: %s <host_ip> <port>\n", argv[0]);
    }
}
