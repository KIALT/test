#include "redis_pubsub.h"

RedisPublisher::RedisPublisher(const RedisOption &option) : RedisAsyncBase(option) {}

RedisPublisher::~RedisPublisher() {}

void RedisPublisher::Publish(std::string_view channel, std::string_view message) {
    std::lock_guard<std::mutex> lock(mutex_);
    redisAsyncCommand(ac_, OnPublishCallback, this, "PUBLISH %s %s", channel.data(), message.data());
}

void RedisPublisher::OnPublishCallback(struct redisAsyncContext *ac, void *r, void *privdata) {}

RedisSubscriber::RedisSubscriber(const RedisOption &option) : RedisAsyncBase(option) {}

RedisSubscriber::~RedisSubscriber() {}

void RedisSubscriber::Subscribe(std::string_view channel, SubscribeFn &&fn) {
    std::lock_guard<std::mutex> lock(mutex_);
    subscribers_[std::string(channel)] = std::move(fn);
    redisAsyncCommand(ac_, OnSubscribeCallback, this, "SUBSCRIBE %s", channel.data());
}

void RedisSubscriber::Unsubscribe(std::string_view channel) {
    std::lock_guard<std::mutex> lock(mutex_);
    subscribers_.erase(std::string(channel));
    redisAsyncCommand(ac_, OnUnsubscribeCallback, this, "UNSUBSCRIBE %s", channel.data());
}

void RedisSubscriber::OnConnect(int status) {
    if (status == REDIS_OK) {
        for (const auto &[channel, fn]: subscribers_) {
            redisAsyncCommand(ac_, OnSubscribeCallback, this, "SUBSCRIBE %s", channel.data());
        }
    }
}

void RedisSubscriber::OnSubscribeCallback(struct redisAsyncContext *ac, void *r, void *privdata) {
    auto self  = static_cast<RedisSubscriber *>(privdata);
    auto reply = static_cast<redisReply *>(r);
    if (reply->type == REDIS_REPLY_ARRAY) {
        if (reply->elements == 3) {
            auto channel = std::string_view(reply->element[1]->str, reply->element[1]->len);
            auto message = std::string_view(reply->element[2]->str, reply->element[2]->len);
            auto fn      = self->subscribers_.find(channel.data());
            if (fn != self->subscribers_.end()) {
                fn->second(channel, message);
            }
        }
    }
}

void RedisSubscriber::OnUnsubscribeCallback(struct redisAsyncContext *ac, void *r, void *privdata) {}
