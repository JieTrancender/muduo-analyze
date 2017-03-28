/*************************************************************************
	> File Name: examples/testLongLifeFactory.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月27日 星期一 22时23分28秒
 ************************************************************************/

#include "../stock-factory.hpp"
#include <cassert>

using namespace std;

void testLongLifeFactory()
{
    shared_ptr<StockFactory> factory(new StockFactory);
    {
        shared_ptr<Stock> stock = factory->get("NYSE:IBM");
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
    }
}

void testShortLifeFactory()
{
    shared_ptr<Stock> stock;
    {
        shared_ptr<StockFactory> factory(new StockFactory);
        stock = factory->get("NYSE:IBM");
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
    }
}

int main(int argc, char* argv[])
{
    testLongLifeFactory();
    testShortLifeFactory();
}
