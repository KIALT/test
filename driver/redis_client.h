#pragma once

#include "redis_command.h"
#include "redis_option.h"
#include "redis_reply.h"
#include <hiredis/hiredis.h>


class RedisPipeline : public RedisCommand
{
public:
    RedisPipeline(struct redisContext *c);
    ~RedisPipeline();

    void                    Clear();
    std::vector<RedisReply> Execute();

private:
    struct redisContext *c_;
    int                  argc_;

    RedisReply DoCommand(std::string_view fmt, ...) noexcept override;
    RedisReply DoCommandArgv(int argc, const char **argv, size_t argvlen[]) noexcept override;
};

class RedisClient : public RedisCommand
{
public:
    RedisClient(const RedisOption &option);
    ~RedisClient();

    bool          Connect(int timeout = 1000);
    void          Close();
    bool          IsConnected() const;
    bool          Reconnect();
    void          SelectDB(int db);
    RedisPipeline Pipeline();

private:
    RedisOption          option_;
    struct redisContext *c_;
    int                  db_;

    RedisReply DoCommand(std::string_view fmt, ...) noexcept override;
    RedisReply DoCommandArgv(int argc, const char **argv, size_t argvlen[]) noexcept override;
};
