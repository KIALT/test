#pragma once

#include "noncopy.h"
#include "redis_option.h"
#include <atomic>
#include <hiredis/async.h>

class RedisAsyncBase : public NonCopyable
{
public:
    RedisAsyncBase(const RedisOption &option);
    virtual ~RedisAsyncBase();

    bool IsConnected() const { return connected_; }

protected:
    RedisOption               option_;
    struct redisAsyncContext *ac_;
    std::atomic<bool>         connected_{false};

    virtual void OnConnect(int status);
    virtual void OnDisconnect(int status);

private:
    static void OnConnectCallback(const struct redisAsyncContext *ac, int status);
    static void OnDisconnectCallback(const struct redisAsyncContext *ac, int status);
};
