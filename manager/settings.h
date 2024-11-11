#pragma once

#include <string>
#include <string_view>

enum LanguageEnum {
    LANGUAGE_EN = 0, /* 英文 */
    LANGUAGE_ZH = 1, /* 中文 */
};

struct Settings {
    LanguageEnum language_;             /* 系统语言 */
    bool         allow_modify_conf_;    /* 是否允许修改配置 */
    bool         allow_remote_control_; /* 是否允许远程控制 */
    std::string  data_dir_;             /* 数据保存目录 */
    std::string  log_dir_;              /* 日志目录 */
    int          log_level_;            /* 日志级别 */
    int          log_max_size_;         /* 日志最大大小 */
    int          log_max_backup_;       /* 日志最大备份数 */
    int          log_max_age_;          /* 日志最大保存天数 */
    std::string  redis_host_;           /* Redis主机 */
    int          redis_db_port_;        /* Redis端口 */
    int          redis_mq_port_;        /* Redis消息队列端口 */
    int          redis_conn_timeout_;   /* Redis连接超时时间 */
    std::string  taos_host_;            /* TDengine主机 */
    int          taos_port_;            /* TDengine端口 */
    std::string  taos_user_;            /* TDengine用户 */
    std::string  taos_password_;        /* TDengine密码 */
};
