#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace mqtt_command {

template<typename T>
struct PublishPacket {
    int         id;
    std::string from;
    std::string time;
    std::string project_code;
    std::string project_name;
    T           data;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PublishPacket, id, from, time, project_code, project_name, data);
};

template<typename T>
struct SubscribePacket {
    int         id;
    std::string from;
    std::string time;
    T           data;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SubscribePacket, id, from, time, data);
};

struct DataIndex {
    std::string key1;
    std::string key2;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataIndex, key1, key2);
};

struct DataEntry {
    std::string key1;
    std::string key2;
    std::string value;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataEntry, key1, key2, value);
};

struct DataPullRequest {
    int                    type; /* 0:实时数据 1:配置数据 */
    std::vector<DataIndex> tags;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataPullRequest, type, tags);
};

struct DataPullReply {
    int                    type;
    std::vector<DataEntry> values;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataPullReply, type, values);
};

struct VPNConnectRequest {
    std::string vpn_name;
    std::string vpn_ip;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(VPNConnectRequest, vpn_name, vpn_ip);
};

struct VPNConnectReply {
    int         code;
    std::string message;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(VPNConnectReply, code, message);
};

struct ConfigModifyRequest {
    std::string config;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigModifyRequest, config);
};

struct ConfigModifyReply {
    int         code;
    std::string message;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigModifyReply, code, message);
};

//控制请求
struct ControlRequest {
    std::string method;
    std::string key1;
    std::string key2;
    std::string command;
    double      value;
    int         type;
    int         status;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlRequest, method, key1, key2, value, type, status);
};

struct ControlReply {
    int         code;
    std::string message;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ControlReply, code, message);
};

struct HistoryDataQueryRequest {
    std::string            start_time;
    std::string            end_time;
    std::string            interval;
    int                    type;
    std::vector<DataIndex> tags;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(HistoryDataQueryRequest, start_time, end_time, tags);
};

struct HistoryDataQueryReply {
    int                    type;
    std::vector<DataEntry> values;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(HistoryDataQueryReply, type, values);
};

}// namespace mqtt_command
