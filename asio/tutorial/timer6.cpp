/*************************************************************************
	> File Name: timer6.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: Thu Jun 15 21:18:36 2017
 ************************************************************************/

#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>

#include <cstdio>
#include <memory>

#include <boost/function.hpp>
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
        printf("Final count is %d\n", count_);
    }

    void print1()
    {
        bool shouldQuit = false;
        int count = 0;

        {
            muduo::MutexLockGuard lock(mutex_);
            if (count_ < 10)
            {
                count = count_;
                ++count_;
            }
            else
            {
                shouldQuit = true;
            }
        }

        if (shouldQuit)
        {
            loop1_->quit();
        }
        else
        {
            printf("TImer 1: %d\n", count);
            boost::function<void()> func1(std::bind(&Printer::print1, this));
            loop1_->runAfter(1, func1);
        }
    }

    void print2()
    {
        bool shouldQuit = false;
        int count = 0;

        {
            muduo::MutexLockGuard lock(mutex_);
            if (count_ < 10)
            {
                count = count_;
                ++count_;
            }
            else
            {
                shouldQuit = true;
            }
        }

        if (shouldQuit)
        {
            loop2_->quit();
        }
        else
        {
            printf("TImer 2: %d\n", count);
            boost::function<void()> func2(std::bind(&Printer::print2, this));
            loop2_->runAfter(1, func2);
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
