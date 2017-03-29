/*************************************************************************
	> File Name: three.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 10时58分46秒
 ************************************************************************/

#include <iostream>

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace std;

using namespace muduo;
using namespace muduo::net;

void onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        conn->shutdown();
    }
}

int main(int argc, char* argv[])
{
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1080), "Finger");
    server.setConnectionCallback(onConnection);
    server.start();
    loop.loop();
}
