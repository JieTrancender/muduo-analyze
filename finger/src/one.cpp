/*************************************************************************
	> File Name: one.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 10时47分18秒
 ************************************************************************/

#include <iostream>

#include <muduo/net/EventLoop.h>

using namespace std;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char* argv[])
{
    EventLoop loop;
    loop.loop();
}
