#pragma once

#include "redis_async.h"
#include <functional>
#include <map>
#include <mutex>
#include <string_view>

class RedisPublisher : public RedisAsyncBase
{
public:
    explicit RedisPublisher(const RedisOption &option);
    ~RedisPublisher();

    void Publish(std::string_view channel, std::string_view message);

private:
    std::mutex mutex_;

    static void OnPublishCallback(struct redisAsyncContext *ac, void *r, void *privdata);
};

class RedisSubscriber : public RedisAsyncBase
{
public:
    using SubscribeFn = std::function<void(std::string_view channel, std::string_view message)>;

    explicit RedisSubscriber(const RedisOption &option);
    ~RedisSubscriber();

    void Subscribe(std::string_view channel, SubscribeFn &&fn);
    void Unsubscribe(std::string_view channel);

private:
    std::mutex                         mutex_;
    std::map<std::string, SubscribeFn> subscribers_;

    void        OnConnect(int status) override;
    static void OnSubscribeCallback(struct redisAsyncContext *ac, void *r, void *privdata);
    static void OnUnsubscribeCallback(struct redisAsyncContext *ac, void *r, void *privdata);
};
