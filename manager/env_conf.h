#pragma once

#include "env_init_conf.h"
#include "env_struct_conf.h"
#include "env_sys_conf.h"
#include "env_work_conf.h"
#include <string>
#include <string_view>

class EnvConf
{
public:
    void Init(std::string_view root_dir);
    bool LoadInitConf();
    bool LoadSysConf();
    bool LoadStructConf();
    bool LoadWorkConf();

    EnvInitConf   init_conf_;   /* 初始化配置 */
    EnvStructConf struct_conf_; /* 结构配置 */
    EnvSysConf    sys_conf_;    /* 系统配置 */
    EnvWorkConf   work_conf_;   /* 工作配置 */
    std::string   err_msg_;     /* 错误信息 */

private:
    static constexpr std::string_view kInitConfPath   = "config/Init.xml"; /* 初始化配置文件路径 */
    static constexpr std::string_view kSysConfPath    = "sys/Sys.xml";     /* 系统配置文件路径 */
    static constexpr std::string_view kStructConfName = "Structure.xml";   /* 结构配置文件名称 */
    static constexpr std::string_view kWorkConfName   = "WorkConfig.xml";  /* 工作配置文件名称 */
};
