/*************************************************************************
	> File Name: main.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月28日 星期二 16时58分39秒
 ************************************************************************/

#include "echo.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(2007);
    EchoServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}
