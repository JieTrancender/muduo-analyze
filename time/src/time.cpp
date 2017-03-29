/*************************************************************************
	> File Name: time.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 13时34分42秒
 ************************************************************************/

#include "time.h"
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

#include <functional>

using namespace std::placeholders;

using namespace muduo;
using namespace muduo::net;

TimeServer::TimeServer(EventLoop* loop, const InetAddress& listenAdder)
    :loop_(loop), server_(loop, listenAdder, "TimeServer")
{
    server_.setConnectionCallback(std::bind(&TimeServer::onConnection, this, _1));
}

void TimeServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "TimeServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        time_t now = ::time(NULL);
        int32_t be32 = sockets::hostToNetwork32(static_cast<int32_t>(now));
        conn->send(&be32, sizeof be32);
        conn->shutdown();
    }
}

void TimeServer::start()
{
    server_.start();
}
