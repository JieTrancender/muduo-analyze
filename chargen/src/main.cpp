/*************************************************************************
	> File Name: main.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 14时45分28秒
 ************************************************************************/

#include "chargen.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    EventLoop loop;
    InetAddress listenAddr(2017);
    ChargenServer server(&loop, listenAddr);
    server.start();
    loop.loop();
}
