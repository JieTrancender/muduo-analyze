/*************************************************************************
	> File Name: time_main.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 13时42分55秒
 ************************************************************************/

#include "time.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <iostream>

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    muduo::net::EventLoop loop;
    TimeServer server(&loop, muduo::net::InetAddress(2017));
    server.start();
    loop.loop();
}
