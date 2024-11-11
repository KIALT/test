#pragma once

#include <string>

struct EnvInitConf {
    std::string path_;         /* 配置文件路径 */
    std::string project_name_; /* 项目名称 */
    std::string project_code_; /* 项目编码 */
    std::string address_;      /* 工程地址 */
    std::string latitude_;     /* 纬度 */
    std::string longitude_;    /* 经度 */
    std::string current_cfg_;  /* 当前配置文件夹名称 */

    bool Load(const std::string &path, std::string &err_msg);
};
