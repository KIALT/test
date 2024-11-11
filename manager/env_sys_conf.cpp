#include "env_sys_conf.h"
#include "fmt.h"

bool EnvSysConf::Load(const std::string &path, std::string &err_msg) {
    tinyxml2::XMLDocument doc;
    EnvSysConf            conf;
    auto                  result = doc.LoadFile(path.c_str());
    if (result != tinyxml2::XML_SUCCESS) {
        err_msg = fmt::format("load env sys conf failed path: {}", path);
        return false;
    }

    auto root = doc.RootElement();
    if (!root) {
        err_msg = "load env sys conf failed root element is null";
        return false;
    }

    auto info_element = root->FirstChildElement("Info");
    if (info_element) {
        auto dev_element = info_element->FirstChildElement("Dev");
        if (dev_element) {
            auto name_attr = dev_element->Attribute("Name");
            auto id_attr   = dev_element->Attribute("Id");
            if (name_attr && id_attr) {
                conf.sys_dev_id_   = std::stoi(id_attr);
                conf.sys_dev_name_ = name_attr;
            }
        }

        auto dev_type_element = info_element->FirstChildElement("DevType");
        if (dev_type_element) {
            auto type_id_attr = dev_type_element->Attribute("TypeID");
            auto main_ip_attr = dev_type_element->Attribute("MainIp");
            if (type_id_attr && main_ip_attr) {
                conf.sys_main_ip_ = main_ip_attr;
                conf.sys_type_id_ = std::stoi(type_id_attr);
            }
        }
    }

    return true;
}
