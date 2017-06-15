/*************************************************************************
	> File Name: test_auto.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月15日 星期四 08时20分19秒
 ************************************************************************/

#include <iostream>

using namespace std;

class A
{
public:
    static const auto a = 'a';
    static const char c = 'c';
    static const auto b = 'b';
};

int main(int argc, char* argv[])
{
    A a;
    cout << a.a << endl;
    cout << a.b << endl;
    cout << a.c << endl;


}
