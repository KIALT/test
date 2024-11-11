#include "redis_reply.h"

RedisReply::RedisReply(redisReply *reply, bool owner)
: reply_(reply,
         [owner](redisReply *reply) {
             if (owner) {
                 freeReplyObject(reply);
             }
         }),
  owner_(owner) {}

RedisReply::RedisReply() : reply_(nullptr, [](redisReply *) {}), owner_(false) {}

RedisReply::~RedisReply() = default;

RedisReply::RedisReply(RedisReply &&other) noexcept {
    reply_ = std::exchange(other.reply_, nullptr);
    owner_ = std::exchange(other.owner_, false);
}

RedisReply &RedisReply::operator=(RedisReply &&other) noexcept {
    if (this != &other) {
        reply_ = std::exchange(other.reply_, nullptr);
        owner_ = std::exchange(other.owner_, false);
    }
    return *this;
}

bool RedisReply::IsOK() const { return !IsNil() && reply_->type == REDIS_REPLY_STATUS && AsStatus() == "OK"; }

RedisReply RedisReply::ArrayAt(int index) const {

    if (IsNil() || reply_->type != REDIS_REPLY_ARRAY || index < 0 || index >= reply_->elements) {
        return {};
    }

    return RedisReply(reply_->element[index], false);
}

RedisReply RedisReply::operator[](int index) const { return ArrayAt(index); }
