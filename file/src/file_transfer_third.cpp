/*************************************************************************
	> File Name: file_transfer_second.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月09日 星期日 18时44分22秒
 ************************************************************************/

#include <muduo/base/Logging.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include <iostream>
#include <cstdio>
#include <memory>

//using namespace std;
using namespace muduo;
using namespace muduo::net;

const int kBufSize = 64 * 1024;
const char* g_file = nullptr;
typedef std::shared_ptr<FILE> FilePtr;

void onHighWaterMark(const TcpConnectionPtr& conn, size_t len)
{
    LOG_INFO << "HighWaterMark" << len;
}

void onConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << "FileServer - " << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        LOG_INFO << "FileServer - Send file " << g_file << " to " << conn->peerAddress().toIpPort();
        conn->setHighWaterMarkCallback(onHighWaterMark, kBufSize + 1);

        FILE* fp = ::fopen(g_file, "rb");
        if (fp)
        {
            FilePtr ctx(fp, ::fclose);
            conn->setContext(ctx);
            char buf[kBufSize];
            size_t nread = ::fread(buf, 1, sizeof buf, fp);
            conn->send(buf, nread);
        }
        else
        {
            conn->shutdown();
            LOG_INFO << "FileServer - no such file.";
        }
    }
}

void onWriteComplete(const TcpConnectionPtr& conn)
{
    const FilePtr& fp = boost::any_cast<const FilePtr&>(conn->getContext());
    char buf[kBufSize];
    size_t nread = ::fread(buf, 1, sizeof buf, get_pointer(fp));
    if (nread > 0)
    {
        conn->send(buf, nread);
    }
    else
    {
        conn->shutdown();
        LOG_INFO << "FileServer - done";
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
