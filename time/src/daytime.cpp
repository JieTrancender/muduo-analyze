/*************************************************************************
	> File Name: daytime.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 12时08分32秒
 ************************************************************************/

#include "daytime.h"
#include <muduo/base/Logging.h>

#include <functional>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

DaytimeServer::DaytimeServer(EventLoop* loop, const InetAddress& listenAddr)
    :loop_(loop), server_(loop, listenAddr, "DaytimeServer")
{
    server_.setConnectionCallback(std::bind(&DaytimeServer::onConnection, this, _1));
}

void DaytimeServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "DaytimeServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        conn->send(Timestamp::now().toFormattedString() + "\n");
        conn->shutdown();
    }
}

void DaytimeServer::start()
{
    server_.start();
}
