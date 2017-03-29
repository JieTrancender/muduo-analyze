/*************************************************************************
	> File Name: time.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 13时32分02秒
 ************************************************************************/
#pragma once

#include <muduo/net/TcpServer.h>

class TimeServer
{
public:
    TimeServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;
};
