#pragma once

#include "entry.h"
#include <string>
#include <string_view>

class EnvStructConf
{
public:
    std::string                  path_;          /* 配置文件路径 */
    std::string                  content_;       /* 文件内容 */
    time_t                       modify_time_;   /* 文件修改时间 */
    std::vector<MultiEntry<int>> rtime_entries_; /* 时间序列数据 */
    std::vector<std::string>     history_tags_;  /* 历史数据标签 */

    bool Load(std::string_view path, std::string &err_msg);

private:
    bool LoadContent(std::string_view path, std::string &err_msg);
    bool ParseContent(std::string_view content, std::string &err_msg);
};
