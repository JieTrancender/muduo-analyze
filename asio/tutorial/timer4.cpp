/*************************************************************************
	> File Name: timer4.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 19:14:40 2017
 ************************************************************************/

#include <muduo/net/EventLoop.h>
#include <muduo/base/Thread.h>

#include <iostream>
#include <functional>

class Printer
{
public:
    Printer(muduo::net::EventLoop* loop)
        : loop_(loop),
          count_(0)
    {
        muduo::Thread::ThreadFunc func(std::bind(&Printer::print, this));
        loop_->runAfter(1, func);
    }

    ~Printer()
    {
        std::cout << "Final count is " << count_ << "\n";
    }

    void print()
    {
        if (count_ < 5)
        {
            std::cout << count_ << "\n";
            ++count_;
            
            muduo::Thread::ThreadFunc func(std::bind(&Printer::print, this));
            loop_->runAfter(1, func);
        }
        else
        {
            loop_->quit();
        }
    }

private:
    muduo::net::EventLoop* loop_;
    int count_;
};

int main(int argc, char* argv[])
{
    muduo::net::EventLoop loop;
    Printer printer(&loop);
    loop.loop();
}
