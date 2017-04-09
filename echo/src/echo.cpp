/*************************************************************************
	> File Name: echo.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月28日 星期二 16时48分23秒
 ************************************************************************/

#include "echo.h"
#include <muduo/base/Logging.h>

#include <functional>
#include <tuple>

using namespace std::placeholders; // for _1, _2, _3

void EchoServer::start()
{
    server_.start();
}

EchoServer::EchoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr)
    : loop_(loop), server_(loop, listenAddr, "EchoServer")
{
    server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
    //server_.setConnectionCallback(boost::bind(&EchoServer::onConnection, this, _1));
    server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1, _2, _3));
    //server_.setMessageCallback(boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> " 
        << conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
}

auto toggleCase = [](int ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = tolower(ch);
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        ch = toupper(ch);
    }
    return ch;
};

auto rot13 = [](int ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 13 > 'Z' ? ch - 13 : ch + 13;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        ch = ch + 13 > 'z' ? ch - 13 : ch + 13;
    }
    return ch;
};

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, " << "data received at " << time.toString();
    //convert uppercase to lowercase and convert lowercase to uppercase
    //transform(msg.begin(), msg.end(), msg.begin(), toggleCase);
    
    //rot13
    transform(msg.begin(), msg.end(), msg.begin(), rot13);
    conn->send(msg);
}
