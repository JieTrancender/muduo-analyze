/*************************************************************************
	> File Name: ofstream_test.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 17时47分54秒
 ************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ofstream out("out.txt");
    if (out.is_open())
    {
        out << "This is a line.\n";
        out << "This is another line.\n";
        out.close();
    }
}
