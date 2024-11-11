#pragma once

#include "entry.h"
#include <string>
#include <string_view>
#include <vector>

class EnvWorkConf
{
public:
    std::string                          path_;           /* 配置文件路径 */
    std::string                          raw_content_;    /* 原始内容 */
    std::string                          json_content_;   /* JSON内容 */
    std::vector<MultiEntry<std::string>> entries_;        /* 多级条目 */
    time_t                               modify_time_{0}; /* 修改时间 */

    bool Load(std::string_view path, std::string &err_msg);

private:
    bool LoadContent(std::string_view path, std::string &err_msg);
    bool ParseContent(std::string_view content, std::string &err_msg);
};
