#pragma once

#include "mqtt_topic_mgr.h"
#include "protocols/mqtt/mqtt_client.h"

class MqttLaunch
{
public:
    MqttLaunch(MqttClient *mqtt_client, MqttTopicMgr *topic_mgr);
    ~MqttLaunch() = default;

    void Publish(std::string_view topic, std::string_view payload);

private:
    MqttClient   *mqtt_client_;
    MqttTopicMgr *topic_mgr_;
};
