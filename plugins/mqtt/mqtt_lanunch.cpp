#include "mqtt_lanunch.h"

MqttLaunch::MqttLaunch(MqttClient *mqtt_client, MqttTopicMgr *topic_mgr)
: mqtt_client_(mqtt_client), topic_mgr_(topic_mgr) {}

void MqttLaunch::Publish(std::string_view topic, std::string_view payload) {
    mqtt_client_->Publish(nullptr, topic, payload);
}
