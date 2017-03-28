#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <mutex>
#include <map>
#include "boost/noncopyable"

class Stock
{
public:
    Stock(std::string str) : m_code(str) {}  //no content
private:
    String m_code;
};

class StockFactory : public std::enable_shared_from_this<StockFactory>, boost::noncopyable
{
public:
    StockFactory() = default;
    ~StockFactory() = default;
public:
    std::shared_ptr<Stock> get(const string& key)
    {
        std::shared_ptr<Stock> pStock;
        std::lock_guard<std::mutex> lock(mutex_);
        std::weak_ptr<Stock>& wkStock = stocks_[key];  //reference
        pStock = wkStock.lock();
        if (!pStock)
        {
            //强制将shared_from_this()转型为weak_ptr，才不会延长生命期
            //因为std::bind拷贝的是实参类型，不是行参类型
            pStock.reset(new Stock(key), std::bind(&StockFactory::weakDeleteCallback, std::weak_ptr<StockFactory>(std::shared_from_this()), _1));
            wkStock = pStock;
        }
        return pStock;
    }
private:
    static void weakDeleteCallback(const std::weak_ptr<StockFactory>& wkFactory, Stock& stock)
    {
        std::shared_ptr<StockFactory> factory(wkFactory.lock());
        if (factory)
        {
            factory->removeStock(stock);
        }
        delete stock;
    }

    void removeStock(Stock* stock)
    {
        if (stock)
        {
            std::lock_guard lock(mutex_);
            stocks_.erase(stock->key());
        }
    }
private:
    mutable std::mutex mutex_;
    std::map<std::string, std::weak_ptr<Stock> stocks_;
};

