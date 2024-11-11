#include "env_init_conf.h"
#include "fmt.h"
#include <tinyxml2.h>

bool EnvInitConf::Load(const std::string &path, std::string &err_msg) {
    tinyxml2::XMLDocument doc;
    auto                  result = doc.LoadFile(path.c_str());
    if (result != tinyxml2::XML_SUCCESS) {
        err_msg = fmt::format("env init conf load failed path: {}", path);
        return false;
    }

    auto root = doc.RootElement();
    if (!root) {
        err_msg = fmt::format("env init conf load failed path: {}", path);
        return false;
    }

    auto project_element = root->FirstChildElement("Project");
    if (project_element) {
        auto name_attr = project_element->Attribute("Name");
        auto code_attr = project_element->Attribute("Code");
        if (name_attr && code_attr) {
            project_name_ = name_attr;
            project_code_ = code_attr;
        }
    }

    auto addr_element = root->FirstChildElement("Addr");
    if (addr_element) {
        auto address_attr   = addr_element->Attribute("Address");
        auto latitude_attr  = addr_element->Attribute("Latitude");
        auto longitude_attr = addr_element->Attribute("Longitude");
        if (address_attr && latitude_attr && longitude_attr) {
            address_   = address_attr;
            latitude_  = latitude_attr;
            longitude_ = longitude_attr;
        }
    }

    auto current_cfg_element = root->FirstChildElement("CurrentCfg");
    if (current_cfg_element) {
        auto name_attr = current_cfg_element->Attribute("Name");
        if (name_attr) {
            current_cfg_ = name_attr;
        }
    }

    return true;
}
