#pragma once

#include <map>
#include <string>
#include <string_view>
#include <vector>

enum CompressTypeEnum {
    kCompressTypeNone = 0, /* 不压缩 */
    kCompressTypeGzip = 1, /* gzip压缩 */
    kCompressTypeZstd = 2, /* zstd压缩 */
};

#define MQ_PUB_STRUCTURE               "controller/basic/structure"       /* 拓扑文件上传主题 */
#define MQ_PUB_WORK_CONFIG             "controller/basic/work_config"     /* 工作配置上传主题 */
#define MQ_PUB_TARIFF_CONFIG           "controller/basic/tariff"          /* 电价配置上传主题 */
#define MQ_PUB_REAL_TIME_DATA          "controller/data/real_data"        /* 实时数据上传主题 */
#define MQ_PUB_HISTORY_UPLOAD          "controller/data/history_upload"   /* 历史数据上传主题 */
#define MQ_PUB_ALARM_INFO              "controller/data/alarm_info"       /* 报警信息上传主题 */
#define MQ_PUB_SYS_INFO                "controller/data/sys_info"         /* 系统信息上传主题 */
#define MQ_PUB_PROC_INFO               "controller/data/proc_info"        /* 进程信息上传主题 */
#define MQ_PUB_EVENT_INFO              "controller/data/event_info"       /* 事件信息上传主题 */
#define MQ_PUB_LOG_INFO                "controller/data/log_info"         /* 日志信息上传主题 */
#define MQ_PUB_HARDWARE_INFO           "controller/data/hardware_info"    /* 硬件信息上传主题 */
#define MQ_PUB_VPN_STATUS              "controller/status/vpn"            /* VPN状态上传主题 */
#define MQ_PUB_ONLINE_STATUS           "controller/status/online"         /* 节点在线状态上传主题 */
#define MQ_PUB_VPN_CONNECT_ACK         "cloud/control/vpn_ack"            /* VPN连接状态上传主题 */
#define MQ_PUB_CONFIG_MODIFY_ACK       "cloud/control/config_modify_ack"  /* 配置修改状态上传主题 */
#define MQ_PUB_CONTROL_COMMAND         "cloud/control/ctrl_cmd_ack"       /* 控制命令状态上传主题 */
#define MQ_PUB_ALARM_OPERATION         "cloud/control/alarm_action_ack"   /* 报警操作状态上传主题 */
#define MQ_SUB_PULL_WORK_CONFIG        "cloud/pull/{}/work_config"        /* 工作配置拉取主题 */
#define MQ_SUB_PULL_STRUCTURE          "cloud/pull/{}/structure"          /* 拓扑文件拉取主题 */
#define MQ_SUB_PULL_TARIFF_CONFIG      "cloud/pull/{}/tariff"             /* 电价配置拉取主题 */
#define MQ_SUB_PULL_REAL_TIME_DATA     "cloud/pull/{}/real_data"          /* 实时数据拉取主题 */
#define MQ_SUB_PULL_SYS_INFO           "cloud/pull/{}/sys_info"           /* 系统信息拉取主题 */
#define MQ_SUB_PULL_PROC_INFO          "cloud/pull/{}/proc_info"          /* 进程信息拉取主题 */
#define MQ_SUB_PULL_EVENT_INFO         "cloud/pull/{}/event_info"         /* 事件信息拉取主题 */
#define MQ_SUB_PULL_HARDWARE_INFO      "cloud/pull/{}/hardware_info"      /* 硬件信息拉取主题 */
#define MQ_SUB_PULL_HISTORY_QUERY      "cloud/pull/{}/history_query"      /* 历史数据查询主题 */
#define MQ_SUB_PULL_HISTORY_UPLOAD_ACK "cloud/pull/{}/history_upload_ack" /* 历史数据上传应答主题 */
#define MQ_SUB_COMAND_CONTROL          "cloud/control/{}/ctrl_cmd"        /* 控制命令拉取主题 */
#define MQ_SUB_COMAND_VPN_CONNECT      "cloud/control/{}/vpn"             /* VPN连接状态拉取主题 */
#define MQ_SUB_COMAND_CONFIG_MODIFY    "cloud/control/{}/config_modify"   /* 配置修改状态拉取主题 */
#define MQ_SUB_COMAND_ALARM_OPERATION  "cloud/control/{}/alarm_action"    /* 报警操作状态拉取主题 */

struct MqttTopicProperty {
    bool        push_enable;   /* 主动推送使能 */
    int         push_interval; /* 主动推送时间间隔 */
    bool        push_change;   /* 变化推送使能 */
    int         qos;           /* QoS */
    std::string path;          /* 配置路径 */
    int         compress_type; /* 压缩格式 */

    MqttTopicProperty()
    : push_enable(false), push_interval(0), push_change(false), qos(0), compress_type(kCompressTypeNone) {}
    MqttTopicProperty(bool push_enable, int push_interval, bool push_change, int qos, int compress_type)
    : push_enable(push_enable), push_interval(push_interval), push_change(push_change), qos(qos),
      compress_type(compress_type) {}
};

class MqttTopicMgr
{
public:
    MqttTopicMgr(const std::string &project_name, const std::string &project_code);
    ~MqttTopicMgr() = default;

    void              SetPubProperty(const std::string &topic, const MqttTopicProperty &property);
    void              SetSubProperty(const std::string &topic, const MqttTopicProperty &property);
    MqttTopicProperty GetPubProperty(const std::string &topic);
    MqttTopicProperty GetSubProperty(const std::string &topic);
    std::map<std::string, MqttTopicProperty> GetAllPubProperties();
    std::map<std::string, MqttTopicProperty> GetAllSubProperties();
    std::string                              GetProjectName() const { return project_name_; }
    std::string                              GetProjectCode() const { return project_code_; }

private:
    std::string                              project_name_;
    std::string                              project_code_;
    std::map<std::string, MqttTopicProperty> pub_properties_;
    std::map<std::string, MqttTopicProperty> sub_properties_;
};
