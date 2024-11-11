#include "redis_async.h"

#include "singleton.h"
#include <event2/event.h>
#include <hiredis/adapters/libevent.h>
#include <hiredis/async.h>
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <thread>

class RedisAsyncLoop : public Singleton<RedisAsyncLoop>
{
public:
    RedisAsyncLoop() {
        ev_base_    = event_base_new();
        idle_event_ = event_new(ev_base_, -1, EV_TIMEOUT | EV_PERSIST, OnIdle, this);
        event_add(idle_event_, nullptr);
        thread_ = std::thread([this]() { event_base_dispatch(ev_base_); });
    }

    ~RedisAsyncLoop() {
        running_ = false;
        event_del(idle_event_);
        event_free(idle_event_);
        event_base_free(ev_base_);
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    struct event_base *GetEventBase() const {
        return ev_base_;
    }

private:
    struct event_base *ev_base_;
    struct event      *idle_event_;
    std::thread        thread_;
    bool               running_{true};

    static void OnIdle(int fd, short event, void *arg){};
};

RedisAsyncBase::RedisAsyncBase(const RedisOption &option) : option_(option) {
    ac_ = redisAsyncConnect(option_.host.c_str(), option_.port);

    if (ac_->err) {
        printf("RedisAsyncBase - redis connect error: %s\n", ac_->errstr);
        return;
    }

    ac_->data = this;
    redisLibeventAttach(ac_, RedisAsyncLoop::Instance().GetEventBase());
    redisAsyncSetConnectCallback(ac_, OnConnectCallback);
    redisAsyncSetDisconnectCallback(ac_, OnDisconnectCallback);
}

RedisAsyncBase::~RedisAsyncBase() {
    if (ac_) {
        redisAsyncDisconnect(ac_);
        redisAsyncFree(ac_);
    }
}

void RedisAsyncBase::OnConnectCallback(const struct redisAsyncContext *ac, int status) {
    if (status != REDIS_OK) {
        return;
    }

    auto self        = static_cast<RedisAsyncBase *>(ac->data);
    self->connected_ = true;
    self->OnConnect(status);
}

void RedisAsyncBase::OnDisconnectCallback(const struct redisAsyncContext *ac, int status) {
    if (status != REDIS_OK) {
        return;
    }

    auto self        = static_cast<RedisAsyncBase *>(ac->data);
    self->connected_ = false;
    self->OnDisconnect(status);
}

void RedisAsyncBase::OnConnect(int status) {}

void RedisAsyncBase::OnDisconnect(int status) {}