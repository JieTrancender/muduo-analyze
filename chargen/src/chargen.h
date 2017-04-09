/*************************************************************************
	> File Name: chargen.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 14时21分32秒
 ************************************************************************/

#pragma once

#include <muduo/net/TcpServer.h>

class ChargenServer
{
public:
    ChargenServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);
    void start();
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);
    void onWriteComplete(const muduo::net::TcpConnectionPtr& conn);

    muduo::net::EventLoop* loop_;
    muduo::net::TcpServer server_;
    muduo::string message_;
    int transferred_;
};
