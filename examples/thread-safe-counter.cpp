/*************************************************************************
	> File Name: thread-safe-counter.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月27日 星期一 18时36分52秒
 ************************************************************************/

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
//#include <boost/noncopyable>


namespace mtl
{
    class noncopyable
    {
    protected:
#if __cplusplus > 201103L
        constexpr noncopyable() = default;
        ~noncopyable() = default;

        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;
#else
        noncopyable() {};
        ~noncopyable() {};

    private:
        noncopyable(const noncopyable&);
        noncopyable& operator=(const noncopyable&);
#endif
    };
}

//class Counter : boost::noncopyable
class Counter : mtl::noncopyable
{
public:
    Counter() : value_(0) {} //no content

    int64_t value() const;
    int64_t getAndIncrease();
    void print()
    {
        std::cout << getAndIncrease() << std::endl;
    }
private:
    int64_t value_;
    mutable std::mutex mutex_;  //mutable 意味着const成员函数也可以使用non-const成员变量
};

int64_t Counter::value() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return  value_;
}

int64_t Counter::getAndIncrease()
{
    std::lock_guard<std::mutex> lock(mutex_);
    int64_t ret = value_++;
    return ret;
}

int main(int argc, char* argv[])
{
    //since -std=c++14
    using namespace std::chrono_literals;
    Counter counter;

    std::vector<std::thread*> vecThread(10);

    for (auto i = 0; i < 10; ++i)
    {
        vecThread.push_back(new std::thread(&Counter::print, std::ref(counter)));
    }

    for (auto i = vecThread.begin(); i != vecThread.end(); ++i)
    {
        (*i)->join();
        std::this_thread::sleep_for(2s);
    }
}
