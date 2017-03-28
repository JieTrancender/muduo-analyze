/*************************************************************************
	> File Name: test.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月27日 星期一 20时49分05秒
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8};

    auto it = vec.begin();
    while (it != vec.end())
    {
        cout << ' ' << *it << endl;
        if (*it == 5)
        {
            it = vec.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (const int& i : vec)
    {
        cout << i << ' ';
    }
    cout << endl;

}
