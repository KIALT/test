#include "env_struct_conf.h"
#include "fmt.h"
#include "fs.h"
#include "logger.h"
#include <cstdlib>
#include <fstream>
#include <map>
#include <set>
#include <string_view>
#include <tinyxml2.h>

bool EnvStructConf::LoadContent(std::string_view path, std::string &err_msg) {

    std::ifstream ifs(path.data());
    if (!ifs.is_open()) {
        err_msg = fmt::format("EnvStructConf::LoadContent open file failed path: {}", path);
        return false;
    }

    time_t modify_time = fs::GetFileModifyTime(path);
    if (modify_time == modify_time_) {
        err_msg = fmt::format("EnvStructConf::LoadContent file not changed path: {}", path);
        return false;
    }

    modify_time_ = modify_time;
    content_     = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    return true;
}

bool EnvStructConf::ParseContent(const std::string_view content, std::string &err_msg) {

    if (content.empty()) {
        err_msg = "EnvStructConf::ParseContent content is empty";
        return false;
    }

    tinyxml2::XMLDocument doc;
    if (doc.Parse(content.data(), content.size()) != tinyxml2::XML_SUCCESS) {
        err_msg = fmt::format("EnvStructConf::ParseContent() parse content failed: {}", doc.ErrorStr());
        return false;
    }

    auto root_elem = doc.RootElement();
    if (!root_elem) {
        err_msg = "EnvStructConf::ParseContent() root element is null";
        return false;
    }

    auto component_elem = root_elem->FirstChildElement("component");
    if (!component_elem) {
        err_msg = "EnvStructConf::ParseContent() component element is null";
        return false;
    }

    std::map<std::string, std::set<std::pair<std::string, bool>>> mapping;

    auto component_item_elem = component_elem->FirstChildElement("item");
    for (; component_item_elem; component_item_elem = component_item_elem->NextSiblingElement("item")) {

        auto measure_elem = component_item_elem->FirstChildElement("measure");
        auto id_attr      = component_item_elem->Attribute("id");

        if (!id_attr || !measure_elem) {
            continue;
        }

        auto measure_item_elem = measure_elem->FirstChildElement();
        for (; measure_item_elem; measure_item_elem = measure_item_elem->NextSiblingElement()) {

            std::string key1_attr    = measure_item_elem->Attribute("key1");
            std::string key2_attr    = measure_item_elem->Attribute("key2");
            std::string history_attr = measure_item_elem->Attribute("history");

            if (key1_attr.empty() || key2_attr.empty()) {
                key1_attr = id_attr;
                key2_attr = measure_item_elem->Name();
            }

            mapping[key1_attr].insert(std::make_pair(key2_attr, std::atoi(history_attr.c_str())));
        }
    }

    rtime_entries_.clear();
    history_tags_.clear();
    for (auto &[key, val]: mapping) {
        MultiEntry<int> multi_entry(key);
        for (auto &[tag, history]: val) {
            multi_entry.AddEntry({"", tag});
            if (history) {
                history_tags_.push_back(fmt::format("{}_{}", key, tag));
            }
        }
        rtime_entries_.push_back(multi_entry);
    }

    return true;
};

bool EnvStructConf::Load(const std::string_view path, std::string &err_msg) {
    if (!LoadContent(path, err_msg)) {
        return false;
    }

    if (!ParseContent(content_, err_msg)) {
        return false;
    }

    return true;
}
