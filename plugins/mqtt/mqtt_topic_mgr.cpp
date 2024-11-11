#include "mqtt_topic_mgr.h"

MqttTopicMgr::MqttTopicMgr(const std::string &project_name, const std::string &project_code)
: project_name_(project_name), project_code_(project_code) {
    pub_properties_ = {
        {MQ_PUB_STRUCTURE, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_WORK_CONFIG, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_TARIFF_CONFIG, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_REAL_TIME_DATA, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_HISTORY_UPLOAD, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_ALARM_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_SYS_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_PROC_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_EVENT_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_LOG_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_HARDWARE_INFO, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_VPN_STATUS, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_ONLINE_STATUS, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_VPN_CONNECT_ACK, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_CONFIG_MODIFY_ACK, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_CONTROL_COMMAND, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
        {MQ_PUB_ALARM_OPERATION, MqttTopicProperty(true, 0, true, 1, kCompressTypeNone)},
    };

    sub_properties_ = {
        {MQ_SUB_PULL_WORK_CONFIG, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_STRUCTURE, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_TARIFF_CONFIG, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_REAL_TIME_DATA, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_SYS_INFO, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_PROC_INFO, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_EVENT_INFO, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_HARDWARE_INFO, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_HISTORY_QUERY, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_PULL_HISTORY_UPLOAD_ACK, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_COMAND_CONTROL, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_COMAND_VPN_CONNECT, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_COMAND_CONFIG_MODIFY, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
        {MQ_SUB_COMAND_ALARM_OPERATION, MqttTopicProperty(false, 0, false, 1, kCompressTypeNone)},
    };
}

MqttTopicProperty MqttTopicMgr::GetPubProperty(const std::string &topic) { return pub_properties_[topic]; }

MqttTopicProperty MqttTopicMgr::GetSubProperty(const std::string &topic) { return sub_properties_[topic]; }

void MqttTopicMgr::SetPubProperty(const std::string &topic, const MqttTopicProperty &property) {
    pub_properties_[topic] = property;
}

void MqttTopicMgr::SetSubProperty(const std::string &topic, const MqttTopicProperty &property) {
    sub_properties_[topic] = property;
}

std::map<std::string, MqttTopicProperty> MqttTopicMgr::GetAllPubProperties() { return pub_properties_; }

std::map<std::string, MqttTopicProperty> MqttTopicMgr::GetAllSubProperties() {
    std::map<std::string, MqttTopicProperty> result;
    for (auto [topic, property]: sub_properties_) {
        char new_topic[128];
        snprintf(new_topic, sizeof(new_topic), topic.c_str(), project_code_.c_str());
        result[new_topic] = property;
    }
    return result;
}
