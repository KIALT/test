#pragma once

#include <string>
#include <tinyxml2.h>

struct EnvSysConf {
    std::string path_;         /* 配置文件路径 */
    std::string sys_dev_name_; /* 系统设备名称 */
    int         sys_dev_id_;   /* 系统设备ID */
    std::string sys_main_ip_;  /* 系统主IP */
    int         sys_type_id_;  /* 系统类型ID */

    bool Load(const std::string &path, std::string &err_msg);
};
