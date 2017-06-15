/*************************************************************************
	> File Name: test_decltype.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月15日 星期四 08时50分30秒
 ************************************************************************/

#include <iostream>

using namespace std;

struct Foo
{
    int x;
};


int main(int argc, char* argv[])
{
    const Foo foo = Foo();
    decltype(foo.x) a = 0;
    decltype((foo.x)) b = a; //由foo为const限定和(foo.x)为一个左值，所以结果为 const int&

    int c = 2;
    b = c;

}
