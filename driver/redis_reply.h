#pragma once

#include <functional>
#include <hiredis/hiredis.h>
#include <memory>
#include <string>
#include <string_view>

class RedisReply
{
public:
    RedisReply(redisReply *reply, bool owner = true);
    RedisReply();
    ~RedisReply();

    RedisReply(const RedisReply &)            = delete;
    RedisReply &operator=(const RedisReply &) = delete;
    RedisReply(RedisReply &&) noexcept;
    RedisReply &operator=(RedisReply &&) noexcept;

    bool IsOK() const;
    bool IsNil() const { return reply_ == nullptr; }
    bool IsError() const { return IsNil() && reply_->type == REDIS_REPLY_ERROR; }
    bool IsStatus() const { return IsNil() && reply_->type == REDIS_REPLY_STATUS; }
    bool IsInteger() const { return IsNil() && reply_->type == REDIS_REPLY_INTEGER; }
    bool IsString() const { return IsNil() && reply_->type == REDIS_REPLY_STRING; }
    bool IsArray() const { return IsNil() && reply_->type == REDIS_REPLY_ARRAY; }
    int64_t          AsInt() const { return reply_->integer; }
    std::string_view AsString() const { return std::string_view(reply_->str, reply_->len); }
    std::string      AsError() const { return std::string(reply_->str, reply_->len); }
    std::string      AsStatus() const { return std::string(reply_->str, reply_->len); }
    int              ArraySize() const { return reply_->elements; }
    RedisReply       ArrayAt(int index) const;
    RedisReply       operator[](int index) const;

private:
    std::unique_ptr<redisReply, std::function<void(redisReply *)>> reply_;
    bool                                                           owner_;
};
