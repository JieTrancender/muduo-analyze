/*************************************************************************
	> File Name: timer3.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 18:59:24 2017
 ************************************************************************/

#include <muduo/net/EventLoop.h>
#include <muduo/base/Thread.h>

#include <boost/bind.hpp>

#include <iostream>
#include <functional>

void print(muduo::net::EventLoop* loop, int *count)
{
    if (*count < 5)
    {
        std::cout << *count << "\n";
        ++(*count);

        //muduo::Thread::ThreadFunc func(print);
        //loop->runAfter(1, std::bind(func, loop, count));
        muduo::Thread::ThreadFunc func(std::bind(print, loop, count));
        loop->runAfter(1, func);
    }
    else
    {
        loop->quit();
    }
}

int main(int argc, char* argv[])
{
    muduo::net::EventLoop loop;
    int count = 0;
    muduo::Thread::ThreadFunc func(std::bind(print, &loop, &count));
    loop.runAfter(1, func);
    loop.loop();
    std::cout << "Final count is " << count << "\n";

}
