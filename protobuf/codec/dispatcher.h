/*************************************************************************
	> File Name: dispatcher.h
	> Author: Jason
	> Mail: jie-email@jie-trancender.org
	> Created Time: 2017年06月12日 星期一 13时13分31秒
 ************************************************************************/

#ifndef _DISPATCHER_H
#define _DISPATCHER_H

#include <muduo/net/Callbacks.h>

#include <google/protobuf/message.h>

#include <map>

//#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/shared_ptr.hpp>

#include <functional>
#include <memory>

//#ifndef NDEBUG
//#include <boost/static_assert.hpp>
//#include <boost/type_traits/is_base_of.hpp>
//#endif

#ifndef NDEBUG
#include <cassert>
#include <type_traits>
#endif

//typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;
typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

class Callback : boost::noncopyable
{
public:
    virtual ~Callback() {};  // no content
    virtual void onMessage(const muduo::net::TcpConnectionPtr&,
                           const MessagePtr& message,
                           muduo::Timestamp) const = 0;
};

template <typename T>
class CallbackT : public Callback
{
//#ifndef NDEBUG
//    BOOST_STATIC_ASSERT((boost::is_base_if<google::protobuf::Message, T>::value));
//#endif
    
#ifndef NDEBUG
    static_assert(std::is_base_if<google::protobuf::Message, T>::value);
#endif
public:
    typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const std::shared_ptr<T>& message,
                                muduo::Timestamp)> ProtobufMessageTCallback;
    
    CallbackT(const ProtobufMessageTCallback& callback)
        : callback_(callback)
    {}  // no content

    virtual void onMessage(const Muduo::net::TcpConnectionPtr& conn,
                           const MessagePtr& message,
                           muduo::Timestamp receiveTime) const
    {
        std::shared_ptr<T> concrete = muduo::down_pointer_cast<T>(message);
        assert(concrete != NULL);
        callback_(conn, concrete, receiveTime);
    }

private:
    ProtobufMessageTCallback callback_;
};
