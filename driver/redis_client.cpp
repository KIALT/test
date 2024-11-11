#include "redis_client.h"

RedisPipeline::RedisPipeline(struct redisContext *c) : c_(c) {}

RedisPipeline::~RedisPipeline() { Clear(); }

RedisReply RedisPipeline::DoCommand(std::string_view fmt, ...) {
    argc_++;

    va_list ap;
    va_start(ap, fmt);
    redisAppendCommand(c_, fmt.data(), ap);
    va_end(ap);
    return {};
}

RedisReply RedisPipeline::DoCommandArgv(int argc, const char **argv, size_t argvlen[]) {
    argc_ += argc;
    redisAppendCommandArgv(c_, argc, argv, argvlen);
    return {};
}

void RedisPipeline::Clear() { argc_ = 0; }

std::vector<RedisReply> RedisPipeline::Execute() {
    std::vector<RedisReply> replies;
    replies.reserve(argc_);

    for (int i = 0; i < argc_; i++) {
        redisReply *reply = nullptr;
        redisGetReply(c_, (void **) &reply);
        replies.emplace_back(reply);
    }

    return replies;
}

RedisClient::RedisClient(const RedisOption &option) : option_(option), c_(nullptr) {}

RedisClient::~RedisClient() { Close(); }

bool RedisClient::Connect(int timeout) {
    struct timeval tv;
    tv.tv_sec  = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    c_ = redisConnectWithTimeout(option_.host.c_str(), option_.port, tv);
    if (c_ == nullptr || c_->err) {
        if (c_) {
            printf("Connection error: %s\n", c_->errstr);
            redisFree(c_);
        }
        return false;
    }

    if (option_.password.empty()) {
        RedisReply reply = DoCommand("AUTH %s", option_.password.c_str());
        if (!reply.IsOK()) {
            redisFree(c_);
            return false;
        }
    }

    SelectDB(option_.db);

    /* 使能keepalive */
    redisEnableKeepAlive(c_);

    return true;
}

void RedisClient::Close() {
    if (c_) {
        redisFree(c_);
        c_ = nullptr;
    }
}

bool RedisClient::IsConnected() const { return c_ != nullptr && c_->err == 0; }

bool RedisClient::Reconnect() { return redisReconnect(c_) == REDIS_OK; }

void RedisClient::SelectDB(int db) {
    if (db != db_) {
        db_ = db;
    }
}

RedisPipeline RedisClient::Pipeline() { return RedisPipeline(c_); }

RedisReply RedisClient::DoCommand(std::string_view fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    RedisReply reply((redisReply *) redisvCommand(c_, fmt.data(), ap));
    va_end(ap);
    return reply;
}

RedisReply RedisClient::DoCommandArgv(int argc, const char **argv, size_t argvlen[]) {
    return RedisReply((redisReply *) redisCommandArgv(c_, argc, argv, argvlen));
}
