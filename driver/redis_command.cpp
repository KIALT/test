#include "redis_command.h"

RedisReply RedisCommand::Ping() { return DoCommand("PING"); }

RedisReply RedisCommand::Select(int db) { return DoCommand("SELECT %d", db); }

RedisReply RedisCommand::Set(std::string_view key, std::string_view value) {
    return DoCommand("SET %b %b", key.data(), key.size(), value.data(), value.size());
}

RedisReply RedisCommand::Get(std::string_view key) { return DoCommand("GET %b", key.data(), key.size()); }

RedisReply RedisCommand::Del(std::string_view key) { return DoCommand("DEL %b", key.data(), key.size()); }

RedisReply RedisCommand::Incr(std::string_view key) { return DoCommand("INCR %b", key.data(), key.size()); }

RedisReply RedisCommand::Decr(std::string_view key) { return DoCommand("DECR %b", key.data(), key.size()); }

RedisReply RedisCommand::IncrBy(std::string_view key, int64_t increment) {
    return DoCommand("INCRBY %b %lld", key.data(), key.size(), increment);
}

RedisReply RedisCommand::DecrBy(std::string_view key, int64_t decrement) {
    return DoCommand("DECRBY %b %lld", key.data(), key.size(), decrement);
}

RedisReply RedisCommand::IncrByFloat(std::string_view key, double increment) {
    return DoCommand("INCRBYFLOAT %b %f", key.data(), key.size(), increment);
}

RedisReply RedisCommand::DecrByFloat(std::string_view key, double decrement) {
    return DoCommand("DECRBYFLOAT %b %f", key.data(), key.size(), decrement);
}

RedisReply RedisCommand::Append(std::string_view key, std::string_view value) {
    return DoCommand("APPEND %b %b", key.data(), key.size(), value.data(), value.size());
}

RedisReply RedisCommand::GetRange(std::string_view key, int start, int end) {
    return DoCommand("GETRANGE %b %d %d", key.data(), key.size(), start, end);
}

RedisReply RedisCommand::HSet(std::string_view key, std::string_view field, std::string_view value) {
    return DoCommand("HSET %b %b %b", key.data(), key.size(), field.data(), field.size(), value.data(), value.size());
}

RedisReply RedisCommand::HGet(std::string_view key, std::string_view field) {
    return DoCommand("HGET %b %b", key.data(), key.size(), field.data(), field.size());
}

RedisReply RedisCommand::HDel(std::string_view key, std::string_view field) {
    return DoCommand("HDEL %b %b", key.data(), key.size(), field.data(), field.size());
}

RedisReply RedisCommand::HIncrBy(std::string_view key, std::string_view field, int64_t increment) {
    return DoCommand("HINCRBY %b %b %lld", key.data(), key.size(), field.data(), field.size(), increment);
}

RedisReply RedisCommand::HDecrBy(std::string_view key, std::string_view field, int64_t decrement) {
    return DoCommand("HDECRBY %b %b %lld", key.data(), key.size(), field.data(), field.size(), decrement);
}

RedisReply RedisCommand::HIncrByFloat(std::string_view key, std::string_view field, double increment) {
    return DoCommand("HINCRBYFLOAT %b %b %f", key.data(), key.size(), field.data(), field.size(), increment);
}

RedisReply RedisCommand::HDecrByFloat(std::string_view key, std::string_view field, double decrement) {
    return DoCommand("HDECRBYFLOAT %b %b %f", key.data(), key.size(), field.data(), field.size(), decrement);
}

RedisReply RedisCommand::HSetNx(std::string_view key, std::string_view field, std::string_view value) {
    return DoCommand("HSETNX %b %b %b", key.data(), key.size(), field.data(), field.size(), value.data(), value.size());
}

RedisReply RedisCommand::HGetAll(std::string_view key) { return DoCommand("HGETALL %b", key.data(), key.size()); }

RedisReply RedisCommand::HKeys(std::string_view key) { return DoCommand("HKEYS %b", key.data(), key.size()); }

RedisReply RedisCommand::HValues(std::string_view key) { return DoCommand("HVALS %b", key.data(), key.size()); }

RedisReply RedisCommand::HGetMap(std::string_view key) { return DoCommand("HGETMAP %b", key.data(), key.size()); }

RedisReply RedisCommand::HSetMap(std::string_view key, const std::vector<std::pair<std::string, std::string>> &map) {
    return DoCommand("HSETMAP %b", key.data(), key.size(), map);
}

RedisReply RedisCommand::HDelMap(std::string_view key, const std::vector<std::string> &fields) {
    return DoCommand("HDELMAP %b", key.data(), key.size(), fields);
}

RedisReply RedisCommand::HExists(std::string_view key, std::string_view field) {
    return DoCommand("HEXISTS %b %b", key.data(), key.size(), field.data(), field.size());
}

RedisReply RedisCommand::HLen(std::string_view key) { return DoCommand("HLEN %b", key.data(), key.size()); }

RedisReply RedisCommand::HMGet(std::string_view key, const std::vector<std::string> &fields) {
    return DoCommand("HMGET %b", key.data(), key.size(), fields);
}

RedisReply RedisCommand::HMSet(std::string_view key, const std::vector<std::pair<std::string, std::string>> &map) {
    return DoCommand("HMSET %b", key.data(), key.size(), map);
}

RedisReply RedisCommand::LIndex(std::string_view key, int index) {
    return DoCommand("LINDEX %b %d", key.data(), key.size(), index);
}

RedisReply RedisCommand::LInsert(std::string_view key, int index, std::string_view value) {
    return DoCommand("LINSERT %b %d %b", key.data(), key.size(), index, value.data(), value.size());
}

RedisReply RedisCommand::LLen(std::string_view key) { return DoCommand("LLEN %b", key.data(), key.size()); }

RedisReply RedisCommand::LPop(std::string_view key) { return DoCommand("LPOP %b", key.data(), key.size()); }

RedisReply RedisCommand::LPush(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("LPUSH %b", key.data(), key.size(), values);
}

RedisReply RedisCommand::LPushX(std::string_view key, std::string_view value) {
    return DoCommand("LPUSHX %b %b", key.data(), key.size(), value.data(), value.size());
}

RedisReply RedisCommand::LRange(std::string_view key, int start, int stop) {
    return DoCommand("LRANGE %b %d %d", key.data(), key.size(), start, stop);
}

RedisReply RedisCommand::LRem(std::string_view key, int count, std::string_view value) {
    return DoCommand("LREM %b %d %b", key.data(), key.size(), count, value.data(), value.size());
}

RedisReply RedisCommand::LSet(std::string_view key, int index, std::string_view value) {
    return DoCommand("LSET %b %d %b", key.data(), key.size(), index, value.data(), value.size());
}

RedisReply RedisCommand::LTrim(std::string_view key, int start, int stop) {
    return DoCommand("LTRIM %b %d %d", key.data(), key.size(), start, stop);
}

RedisReply RedisCommand::RPop(std::string_view key) { return DoCommand("RPOP %b", key.data(), key.size()); }

RedisReply RedisCommand::RPopLPush(std::string_view source, std::string_view destination) {
    return DoCommand("RPOPLPUSH %b %b", source.data(), source.size(), destination.data(), destination.size());
}

RedisReply RedisCommand::RPush(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("RPUSH %b", key.data(), key.size(), values);
}

RedisReply RedisCommand::RPushX(std::string_view key, std::string_view value) {
    return DoCommand("RPUSHX %b %b", key.data(), key.size(), value.data(), value.size());
}

RedisReply RedisCommand::SAdd(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("SADD %b", key.data(), key.size(), values);
}

RedisReply RedisCommand::SCard(std::string_view key) { return DoCommand("SCARD %b", key.data(), key.size()); }

RedisReply RedisCommand::SContains(std::string_view key, std::string_view value) {
    return DoCommand("SCONTAINS %b %b", key.data(), key.size(), value.data(), value.size());
}

RedisReply RedisCommand::SContainsAll(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("SCONTAINSALL %b", key.data(), key.size(), values);
}

RedisReply RedisCommand::SContainsAny(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("SCONTAINSANY %b", key.data(), key.size(), values);
}

RedisReply RedisCommand::SContainsNone(std::string_view key, const std::vector<std::string> &values) {
    return DoCommand("SCONTAINSNONE %b", key.data(), key.size(), values);
}
