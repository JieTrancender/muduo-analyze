/*************************************************************************
	> File Name: echo.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月15日 星期四 11时33分23秒
 ************************************************************************/

#ifndef _ECHO_H
#define _ECHO_H

#include <muduo/net/TcpServer.h>

class EchoServer
{
public:
    EchoServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr, int maxConnections);

    void start();

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);

    muduo::net::TcpServer server_;
    int numConnected_;
    const int kMaxConnections_;
};
#endif
