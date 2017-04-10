/*************************************************************************
	> File Name: server.cpp
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月10日 星期一 09时14分05秒
 ************************************************************************/

#include "codec.h"

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/noncopyable.hpp>

#include <functional>
#include <set>

#include <cstdint>

using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;  //for _1, _2, _3

class ChatServer : boost::noncopyable
{
public:
    ChatServer(EventLoop* loop, const InetAddress& listenAddr)
    :loop_(loop), server_(loop, listenAddr, "ChatServer"),codec_(std::bind(&ChatServer::onStringMessage, this, _1, _2, _3))
    {
        server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        server_.setMessageCallback(std::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
    }

    void start()
    {
        server_.start();
    }

private:
    void onConnection(const TcpConnectionPtr& conn)
    {
        LOG_INFO << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is " 
            << (conn->connected() ? "UP" : "DOWN");

        if (conn->connected())
        {
            connections_.insert(conn);
        }
        else
        {
            connections_.erase(conn);
        }
    }

    void onStringMessage(const TcpConnectionPtr&, const string& message, Timestamp)
    {
        for (auto& it : connections_)
        {
            //codec_.send((*it).get(), message);
            codec_.send(get_pointer(it), message);
        }
        /*for (ConnectionList::iterator it = connections_.begin(); it != connections_.end(); ++it)
        {
            codec_.send(get_pointer(*it), message);
        }*/
    }

    typedef std::set<TcpConnectionPtr> ConnectionList;
    EventLoop* loop_;
    TcpServer server_;
    LengthHeaderCodec codec_;
    ConnectionList connections_;
};

using namespace std;

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = " << getpid();
    if (argc > 1)
    {
        EventLoop loop;
        uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
        InetAddress serverAddr(port);
        ChatServer server(&loop, serverAddr);
        server.start();
        loop.loop();
    }
    else
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    }
}

