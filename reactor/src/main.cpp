/*************************************************************************
	> File Name: main.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 15时03分19秒
 ************************************************************************/

#include "../../chargen/src/chargen.h"
#include "../../time/src/daytime.h"
#include "../../time/src/time.h"
#include "../../echo/src/echo.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    EventLoop loop;

    ChargenServer chargenServer(&loop, InetAddress(20171));
    chargenServer.start();

    DaytimeServer daytimeServer(&loop, InetAddress(20172));
    daytimeServer.start();

    TimeServer timeServer(&loop, InetAddress(20173));
    timeServer.start();

    EchoServer echoServer(&loop, InetAddress(20174));
    echoServer.start();

    loop.loop();
}
