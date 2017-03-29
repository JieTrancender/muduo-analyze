/*************************************************************************
	> File Name: daytime.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 12时05分26秒
 ************************************************************************/
#pragma once

#include <muduo/net/TcpServer.h>

class DaytimeServer
{
public:
    DaytimeServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);
    
    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;
};
