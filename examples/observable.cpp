/*************************************************************************
	> File Name: observable.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月27日 星期一 20时42分54秒
 ************************************************************************/

#include <iostream>

using namespace std;

class Observable
{
public:
    void register(weak_ptr<Observer> x);
    void notifyObservers();
private:
    mutable std::mutex mutex_;
    std::vector<std::weak_ptr<Observer>> observers_;
    typedef std::vector<std::weak_ptr<Observer>>::iterator Iterator;
};

void Observable::notifyObservers()
{
    std::lock_guard<std::mutex> lock(mutex_);
    Iterator it = observers_begin();
    while (it != observers_.end())
    {
        std::shared_ptr<Observer> obj(it->lock());
        if (obj)
        {
            obj->update();
            ++it;
        }
        else
        {
            it = observers_.erase(it);
        }
    }
}

int main(int argc, char* argv[])
{

}
