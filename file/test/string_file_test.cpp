/*************************************************************************
	> File Name: string_file_test.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 17时59分02秒
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string readFile(const char* filename)
{
    ifstream ifile(filename);
    ostringstream buf;
    char ch;

    while (buf && ifile.get(ch))
    {
        buf.put(ch);
    }
    return buf.str();
}

int main(int argc, char* argv[])
{
    const char* filename = "out.txt";
    string str = readFile(filename);
    cout << str << endl;
}
