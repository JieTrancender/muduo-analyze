/*************************************************************************
	> File Name: file_transfer_first.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 18时07分43秒
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

//using namespace std;
using namespace muduo;
using namespace muduo::net;

const char* g_file = nullptr;
std::string readFile(const char* filename);

void onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "FileServer - " << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        LOG_INFO << "FileServer - Send file " << g_file << " to " << conn->peerAddress().toIpPort();
        std::string fileContent = readFile(g_file);
        conn->send(fileContent);
        conn->shutdown();
        LOG_INFO << "FileServer done";
    }
}

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    if (argc > 1)
    {
        g_file = argv[1];

        EventLoop loop;
        InetAddress listenAddr(2017);
        TcpServer server(&loop, listenAddr, "FileServer");
        server.setConnectionCallback(onConnection);
        server.start();
        loop.loop();
    }
    else
    {
        fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
    }
}

std::string readFile(const char* filename)
{
    std::ifstream ifile(filename);
    std::ostringstream buf;
    char ch;

    if (buf && ifile.is_open())
    {
        while (ifile.get(ch))
        {
            buf.put(ch);
        }
        return buf.str();
    }
    else
    {
        fprintf(stderr, "fail to read \"%s\"!", filename);
    }
    return "";
}
