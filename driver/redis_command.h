#pragma once

#include "redis_reply.h"
#include <hiredis/hiredis.h>
#include <string>
#include <string_view>
#include <vector>

class RedisCommand
{
public:
    RedisCommand()          = default;
    virtual ~RedisCommand() = default;

    RedisReply Ping();
    RedisReply Select(int db);
    RedisReply Set(std::string_view key, std::string_view value);
    RedisReply Get(std::string_view key);
    RedisReply Del(std::string_view key);
    RedisReply Incr(std::string_view key);
    RedisReply Decr(std::string_view key);
    RedisReply IncrBy(std::string_view key, int64_t increment);
    RedisReply DecrBy(std::string_view key, int64_t decrement);
    RedisReply IncrByFloat(std::string_view key, double increment);
    RedisReply DecrByFloat(std::string_view key, double decrement);
    RedisReply Append(std::string_view key, std::string_view value);
    RedisReply GetRange(std::string_view key, int start, int end);
    RedisReply HSet(std::string_view key, std::string_view field, std::string_view value);
    RedisReply HGet(std::string_view key, std::string_view field);
    RedisReply HDel(std::string_view key, std::string_view field);
    RedisReply HIncrBy(std::string_view key, std::string_view field, int64_t increment);
    RedisReply HDecrBy(std::string_view key, std::string_view field, int64_t decrement);
    RedisReply HIncrByFloat(std::string_view key, std::string_view field, double increment);
    RedisReply HDecrByFloat(std::string_view key, std::string_view field, double decrement);
    RedisReply HSetNx(std::string_view key, std::string_view field, std::string_view value);
    RedisReply HGetAll(std::string_view key);
    RedisReply HKeys(std::string_view key);
    RedisReply HValues(std::string_view key);
    RedisReply HGetMap(std::string_view key);
    RedisReply HSetMap(std::string_view key, const std::vector<std::pair<std::string, std::string>> &map);
    RedisReply HDelMap(std::string_view key, const std::vector<std::string> &fields);
    RedisReply HExists(std::string_view key, std::string_view field);
    RedisReply HLen(std::string_view key);
    RedisReply HMGet(std::string_view key, const std::vector<std::string> &fields);
    RedisReply HMSet(std::string_view key, const std::vector<std::pair<std::string, std::string>> &map);
    RedisReply LIndex(std::string_view key, int index);
    RedisReply LInsert(std::string_view key, int index, std::string_view value);
    RedisReply LLen(std::string_view key);
    RedisReply LPop(std::string_view key);
    RedisReply LPush(std::string_view key, const std::vector<std::string> &values);
    RedisReply LPushX(std::string_view key, std::string_view value);
    RedisReply LRange(std::string_view key, int start, int stop);
    RedisReply LRem(std::string_view key, int count, std::string_view value);
    RedisReply LSet(std::string_view key, int index, std::string_view value);
    RedisReply LTrim(std::string_view key, int start, int stop);
    RedisReply RPop(std::string_view key);
    RedisReply RPopLPush(std::string_view source, std::string_view destination);
    RedisReply RPush(std::string_view key, const std::vector<std::string> &values);
    RedisReply RPushX(std::string_view key, std::string_view value);
    RedisReply SAdd(std::string_view key, const std::vector<std::string> &values);
    RedisReply SCard(std::string_view key);
    RedisReply SContains(std::string_view key, std::string_view value);
    RedisReply SContainsAll(std::string_view key, const std::vector<std::string> &values);
    RedisReply SContainsAny(std::string_view key, const std::vector<std::string> &values);
    RedisReply SContainsNone(std::string_view key, const std::vector<std::string> &values);

protected:
    virtual RedisReply DoCommand(std::string_view fmt, ...) noexcept = 0;
    virtual RedisReply DoCommandArgv(int argc, const char **argv, size_t argvlen[]) noexcept = 0;
};
