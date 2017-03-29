/*************************************************************************
	> File Name: two.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 10时57分23秒
 ************************************************************************/

#include <iostream>

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace std;

using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1079), "Finger");
    server.start();
    loop.loop();

}
