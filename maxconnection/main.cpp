/*************************************************************************
	> File Name: main.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 17:34:50 2017
 ************************************************************************/

#include "echo.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

using namespace std;

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    EventLoop loop;
    InetAddress listenAddr(2017);
    int maxConnections = 5;
    if (argc > 1)
    {
        maxConnections = atoi(argv[1]);
    }
    LOG_INFO << "maxConnections = " << maxConnections;
    EchoServer server(&loop, listenAddr, maxConnections);
    server.start();
    loop.loop();
}
