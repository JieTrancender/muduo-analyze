/*************************************************************************
	> File Name: timer5.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 19:22:44 2017
 ************************************************************************/

#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>

#include <iostream>
#include <functional>
#include <memory>

#include <boost/noncopyable.hpp>

class Printer : boost::noncopyable
{
public:
    Printer(muduo::net::EventLoop* loop1, muduo::net::EventLoop* loop2)
        : loop1_(loop1),
          loop2_(loop2),
            count_(0)
    {
        boost::function<void()> func1(std::bind(&Printer::print1, this));
        boost::function<void()> func2(std::bind(&Printer::print2, this));
        loop1_->runAfter(1, func1);
        loop2_->runAfter(1, func2);
    }

    ~Printer()
    {
        std::cout << "Final count is " << count_ << "\n";
    }

    void print1()
    {
        muduo::MutexLockGuard lock(mutex_);
        if (count_ < 10)
        {
            std::cout << "Timer 1: " << count_ << "\n";
            ++count_;

            boost::function<void()> func1(std::bind(&Printer::print1, this));
            loop1_->runAfter(1, func1);

        }
        else
        {
            loop1_->quit();
        }
    }

    void print2()
    {
        muduo::MutexLockGuard lock(mutex_);
        if (count_ < 10)
        {
            std::cout << "Timer 2: " << count_ << "\n";
            ++count_;

            boost::function<void()> func2(std::bind(&Printer::print2, this));
            loop2_->runAfter(1, func2);

        }
        else
        {
            loop2_->quit();
        }
    }

private:
    muduo::MutexLock mutex_;
    muduo::net::EventLoop* loop1_;
    muduo::net::EventLoop* loop2_;
    int count_;
};

int main(int argc, char* argv[])
{
    std::unique_ptr<Printer> printer;

    muduo::net::EventLoop loop;
    muduo::net::EventLoopThread loopThread;
    muduo::net::EventLoop* loopInAnotherThread = loopThread.startLoop();
    printer.reset(new Printer(&loop, loopInAnotherThread));
    loop.loop();
}
