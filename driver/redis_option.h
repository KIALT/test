#pragma once

#include <string>

enum RedisDBEnum {
    REDIS_DB_REALTIME = 0, /* 实时数据库 */
    REDIS_DB_CONFIG   = 1, /* 配置数据库 */
    REDIS_DB_ALARM    = 2  /* 告警数据库 */
};

struct RedisOption {
    std::string host;     /* 主机 */
    int         port;     /* 端口 */
    int         db;       /* 数据库 */
    std::string password; /* 密码 */
};

struct RedisPoolOption {
    RedisOption option;          /* 连接参数 */
    int         max_connections; /* 最大连接数 */
    int         min_connections; /* 最小连接数 */
    int         max_idle_time;   /* 最大空闲时间 */
    int         connect_timeout; /* 连接超时 */
};
