/*************************************************************************
	> File Name: echo.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月15日 星期四 11时36分57秒
 ************************************************************************/

#include "echo.h"

#include <muduo/base/Logging.h>
//#include <muduo/base/Timestamp.h>
//#include <muduo/net/EventLoop.h>

#include <functional>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

EchoServer::EchoServer(EventLoop* loop, const InetAddress& listenAddr, int maxConnections)
    : server_(loop, listenAddr, "Echo Server"),
      kMaxConnections_(maxConnections),
      numConnected_(0)
{
    server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::start()
{
    server_.start();
}

void EchoServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort()
        << " is " << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected())
    {
        ++numConnected_;
        if (numConnected_ > kMaxConnections_)
        {
            conn->shutdown();
            conn->forceCloseWithDelay(3.0);
        }
    }
    else
    {
        --numConnected_;
    }
    LOG_INFO << "numConnected_ = " << numConnected_;
}

void EchoServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes at " << time.toString();
    conn->send(msg);
}

