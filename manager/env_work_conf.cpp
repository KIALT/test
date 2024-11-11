#include "entry.h"
#include "env_work_conf.h"
#include "fs.h"
#include "logger.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

bool EnvWorkConf::Load(std::string_view path, std::string &err_msg) {
    if (!LoadContent(path, err_msg)) {
        return false;
    }

    if (!ParseContent(raw_content_, err_msg)) {
        return false;
    }

    return true;
}

bool EnvWorkConf::LoadContent(std::string_view path, std::string &err_msg) {
    std::ifstream ifs(path.data());
    if (!ifs.is_open()) {
        err_msg = fmt::format("EnvWorkConf::LoadContent open file failed path: {}", path);
        return false;
    }

    time_t modify_time = fs::GetFileModifyTime(path);
    if (modify_time_ == modify_time) {
        err_msg = fmt::format("EnvWorkConf::LoadContent file not changed path: {}", path);
        return true;
    }

    modify_time_ = modify_time;
    raw_content_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    return true;
}

bool EnvWorkConf::ParseContent(std::string_view content, std::string &err_msg) {
    if (content.empty()) {
        err_msg = "EnvWorkConf::ParseContent content is empty";
        return false;
    }

    tinyxml2::XMLDocument doc;
    if (doc.Parse(content.data(), content.size()) != tinyxml2::XML_SUCCESS) {
        err_msg = fmt::format("EnvWorkConf::ParseContent error: {}", doc.ErrorStr());
        return false;
    }

    auto root = doc.RootElement();
    if (!root) {
        err_msg = "EnvWorkConf::ParseContent error: root is null";
        return false;
    }

    nlohmann::json mapping_json;
    auto           groups_elem = root->FirstChildElement();
    for (; groups_elem; groups_elem = groups_elem->NextSiblingElement()) {

        auto tags_elem = groups_elem->FirstChildElement();
        for (; tags_elem; tags_elem = tags_elem->NextSiblingElement()) {
            std::string key   = groups_elem->Name();
            std::string field = tags_elem->Name();
            std::string value = tags_elem->GetText();

            try {
                if (value.empty() || value == "--") {
                    continue;
                }
                mapping_json[key][field] = nlohmann::json::parse(value);
            } catch (std::exception &e) {
                mapping_json[key][field] = value;
                Logger::Warn("EnvWorkConf::ParseContent parse json faild key1:{} key2:{} err:{}", key, field, e.what());
            }
        }
    }

    json_content_ = mapping_json.dump();
    return true;
}