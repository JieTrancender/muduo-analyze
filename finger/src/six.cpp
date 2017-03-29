/*************************************************************************
	> File Name: six.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年03月29日 星期三 11时04分13秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <string>

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

//using namespace std;
using namespace muduo;
using namespace muduo::net;

typedef std::map<string, string> UserMap;
UserMap users;

string getUser(const string& user)
{
    string result = "No such user";
    UserMap::iterator it = users.find(user);
    if (it != users.end())
    {
        result = it->second;
    }
    return result;
}

void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
{
    const char* crlf = buf->findCRLF();
    if (crlf)
    {
        string user(buf->peek(), crlf);
        conn->send(getUser(user) + "\r\n");
        buf->retrieveUntil(crlf + 2);
        conn->shutdown();
    }
}

int main(int argc, char* argv[])
{
    EventLoop loop;
    TcpServer server(&loop, InetAddress(1083), "Finger");
    server.setMessageCallback(onMessage);
    server.start();
    loop.loop();
}
