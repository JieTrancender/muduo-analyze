/*************************************************************************
	> File Name: daytime_time.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 12时12分56秒
 ************************************************************************/

#include "daytime.h"
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    EventLoop loop;
    DaytimeServer server(&loop, InetAddress(2017));
    server.start();
    loop.loop();
}
