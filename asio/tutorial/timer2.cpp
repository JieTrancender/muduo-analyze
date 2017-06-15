/*************************************************************************
	> File Name: timer2.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 17:55:23 2017
 ************************************************************************/

#include <muduo/net/EventLoop.h>
#include <muduo/base/Thread.h>

#include <iostream>

void print()
{
    std::cout << "Hello, World!\n";
}

int main(int argc, char* argv[])
{
    muduo::net::EventLoop loop;
    muduo::Thread::ThreadFunc func(print);
    loop.runAfter(5, func);
    loop.loop();
}
