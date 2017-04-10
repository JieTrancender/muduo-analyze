/*************************************************************************
	> File Name: codec.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年04月10日 星期一 08时39分55秒
 ************************************************************************/

#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/TcpConnection.h>

#include <boost/noncopyable.hpp>
//#include <boost/noncopyable.hpp>

#include <functional>

class LengthHeaderCodec : boost::noncopyable
{
public:
    typedef std::function<void (const muduo::net::TcpConnectionPtr& conn, const muduo::string& message, 
                                muduo::Timestamp)> StringMessageCallback;

    explicit LengthHeaderCodec(const StringMessageCallback& cb)
        :messageCallback_(cb) {}  //no content
    
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp receiveTime)
    {
        while (buf->readableBytes() >= kHeaderLen)
        {
            const void* data = buf->peek();
            int32_t be32 = *static_cast<const int32_t*>(data);
            const int32_t len = muduo::net::sockets::networkToHost32(be32);
            if (len > 65536 || len < 0)
            {
                LOG_ERROR << "Invalid length " << len;
                conn->shutdown();  //disable reading
                break;
            }
            else if (buf->readableBytes() >= len + kHeaderLen)
            {
                buf->retrieve(kHeaderLen);
                muduo::string message(buf->peek(), len);
                messageCallback_(conn, message, receiveTime);
                buf->retrieve(len);
            }
            else
            {
                break;
            }
        }
    }

    void send(muduo::net::TcpConnection* conn, const muduo::StringPiece& message)
    {
        muduo::net::Buffer buf;
        buf.append(message.data(), message.size());
        int32_t len = static_cast<int32_t>(message.size());
        int32_t be32 = muduo::net::sockets::hostToNetwork32(len);
        buf.append(&be32, sizeof  be32);
        conn->send(&buf);
    }

private:
    StringMessageCallback messageCallback_;
    const static size_t kHeaderLen = sizeof(int32_t);  //kHeaderLen == 4
};
