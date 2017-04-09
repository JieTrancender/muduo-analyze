/*************************************************************************
	> File Name: ifstream_test.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 17时52分11秒
 ************************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    char buf[256];
    ifstream in("out.txt");
    if (!in.is_open())
    {
        fprintf(stderr, "%s", "Error opening file!");
        exit(1);
    }
    while (!in.eof())
    {
        in.getline(buf, 100);
        cout << buf << endl;
    }
}
