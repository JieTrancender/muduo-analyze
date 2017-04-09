/*************************************************************************
	> File Name: src/chargen.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 14时25分56秒
 ************************************************************************/

#include "chargen.h"
#include <muduo/base/Logging.h>

#include <functional>

using namespace std::placeholders;
using namespace muduo;
using namespace muduo::net;

ChargenServer::ChargenServer(EventLoop* loop, const InetAddress& listenAddr)
    :loop_(loop), server_(loop, listenAddr, "ChargenServer"),message_("Hello World!"),transferred_(0)
{
    server_.setConnectionCallback(std::bind(&ChargenServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&ChargenServer::onMessage, this, _1, _2, _3));
    server_.setWriteCompleteCallback(std::bind(&ChargenServer::onWriteComplete, this, _1));
}

void ChargenServer::start()
{
    server_.start();
}

void ChargenServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "ChargenServer - " << conn->peerAddress().toIpPort() << " -> " 
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        conn->setTcpNoDelay(true);
        conn->send(message_);
    }
}

void ChargenServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " discards " << msg.size() << " bytes received at " << time.toString();
}

void ChargenServer::onWriteComplete(const TcpConnectionPtr& conn)
{
    transferred_ += message_.size();
    conn->send(message_);
}
