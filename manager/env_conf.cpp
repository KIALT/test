#include "env_conf.h"
#include "fmt.h"
#include "logger.h"

void EnvConf::Init(std::string_view root_dir) {

    init_conf_.path_ = fmt::format("{}/{}", root_dir, kInitConfPath);
    sys_conf_.path_  = fmt::format("{}/{}", root_dir, kSysConfPath);

    if (!init_conf_.Load(init_conf_.path_, err_msg_)) {
        Logger::Warn("EnvConf::Init() load init conf failed: {}", err_msg_);
    }

    if (!sys_conf_.Load(sys_conf_.path_, err_msg_)) {
        Logger::Warn("EnvConf::Init() load sys conf failed: {}", err_msg_);
    }

    std::string config_dir = fmt::format("{}/config/{}", root_dir, init_conf_.current_cfg_);
    struct_conf_.path_     = fmt::format("{}/{}", config_dir, kStructConfName);

    if (!struct_conf_.Load(struct_conf_.path_, err_msg_)) {
        Logger::Warn("EnvConf::Init() load struct conf failed: {}", err_msg_);
    }

    work_conf_.path_ = fmt::format("{}/{}", config_dir, kWorkConfName);
    if (!work_conf_.Load(work_conf_.path_, err_msg_)) {
        Logger::Warn("EnvConf::Init() load work conf failed: {}", err_msg_);
    }
}

bool EnvConf::LoadInitConf() {
    bool result = init_conf_.Load(init_conf_.path_, err_msg_);
    if (!result) {
        Logger::Warn("EnvConf::LoadInitConf() load init conf failed: {}", err_msg_);
    }
    return result;
}

bool EnvConf::LoadSysConf() {
    bool result = sys_conf_.Load(sys_conf_.path_, err_msg_);
    if (!result) {
        Logger::Warn("EnvConf::LoadSysConf() load sys conf failed: {}", err_msg_);
    }
    return result;
}

bool EnvConf::LoadStructConf() {
    bool result = struct_conf_.Load(struct_conf_.path_, err_msg_);
    if (!result) {
        Logger::Warn("EnvConf::LoadStructConf() load struct conf failed: {}", err_msg_);
    }
    return result;
}

bool EnvConf::LoadWorkConf() {
    bool result = work_conf_.Load(work_conf_.path_, err_msg_);
    if (!result) {
        Logger::Warn("EnvConf::LoadWorkConf() load work conf failed: {}", err_msg_);
    }
    return result;
}