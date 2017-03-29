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

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTIme)
{
    if (buf->findCRLF())
    {
        conn->send("No such user\r\n");
        conn->shutdown();
    }
}

int main(int argc, char* argv[])
{
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1082), "Finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
}
