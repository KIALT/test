#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <string_view>

namespace helper {

constexpr std::string_view kRealCmdReq      = "real_cmd";              /*  实时数据设置命令请求 */
constexpr std::string_view kRealCmdResp     = "real_cmd_ack";          /*  实时数据设置命令应答 */
constexpr std::string_view kConfigCmdReq    = "config_cmd";            /*  配置数据设置命令请求 */
constexpr std::string_view kConfigCmdResp   = "config_cmd_ack";        /*  配置数据设置命令应答 */
constexpr std::string_view kCtrlCmdReq      = "ctl_cmd";               /*  控制命令请求 */
constexpr std::string_view kCtrlCmdResp     = "ctl_cmd_ack";           /*  控制命令应答 */
constexpr std::string_view kVpnCtrlReq      = "cloud_control_vpn";     /*  VPN连接控制指令请求 */
constexpr std::string_view kVpnCtrlResp     = "cloud_control_vpn_ack"; /*  VPN连接控制指令应答 */
constexpr std::string_view kScheduleCmdReq  = "schedule_cmd";          /*  调度指令请求 */
constexpr std::string_view kScheduleCmdResp = "schedule_cmd_ack";      /*  调度指令应答 */
constexpr std::string_view kScriptCmdReq    = "script_cmd";            /*  脚本指令请求 */
constexpr std::string_view kScriptCmdResp   = "script_cmd_ack";        /*  脚本指令应答 */
constexpr std::string_view kSetStatusReq    = "status_setstatus";      /*  设置状态请求 */
constexpr std::string_view kSetStatusResp   = "status_setstatus_ack";  /*  设置状态应答 */
constexpr std::string_view kAlarmInfo       = "alarm_info";            /*  报警信息推送 */
constexpr std::string_view kAlarmEnable     = "alarm_enable";          /*  报警使能请求 */
constexpr std::string_view kAlarmEnableAck  = "alarm_enable_ack";      /*  报警使能应答 */
constexpr std::string_view kAlarmReset      = "alarm_reset";           /*  报警复位请求 */
constexpr std::string_view kAlarmResetAck   = "alarm_reset_ack";       /*  报警复位应答 */
constexpr std::string_view kAlarmConfirm    = "alarm_confirm";         /*  报警确认请求 */
constexpr std::string_view kAlarmConfirmAck = "alarm_confirm_ack";     /*  报警确认应答 */
constexpr std::string_view kSaveWorkMode    = "save_work_mode";        /*  保存工作模式 */
constexpr std::string_view kHeartbeatInfo   = "heartbeat_info";        /*  心跳信息推送 */
constexpr std::string_view kSysInfo         = "sys_info";              /*  系统信息推送 */
constexpr std::string_view kGetSysInfo      = "cloud_sys_info";        /*  云端系统信息推送 */
constexpr std::string_view kProcInfo        = "proc_info";             /*  进程信息推送 */
constexpr std::string_view kGetProcInfo     = "cloud_proc_info";       /*  云端进程信息推送 */
constexpr std::string_view kEventInfo       = "event_info";            /*  事件信息推送 */
constexpr std::string_view kGetEventInfo    = "cloud_event_info";      /*  云端事件信息推送 */
constexpr std::string_view kHardwareInfo    = "hardware_info";         /*  硬件信息推送 */
constexpr std::string_view kGetHardwareInfo = "cloud_hardware_info";   /*  云端硬件信息推送 */
constexpr std::string_view kLogInfo         = "log_info";              /*  日志信息推送 */
constexpr std::string_view kPing            = "ping";                  /*  心跳信息推送 */

template<typename T>
struct MSGEntry {
    int         id;
    std::string from;
    std::string time;
    std::string ack;
    T           data;

    MSGEntry(int id, std::string_view from, std::string_view time, std::string_view ack)
    : id(id), from(from), time(time), ack(ack) {}

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGEntry, id, from, time, ack, data);
};

struct MSGResultFlow {
    int64_t     id;      /* 消息ID */
    std::string from;    /* 消息来源 */
    std::string time;    /* 消息时间 */
    std::string message; /* 消息内容 */
    int         result;  /* 消息结果 */
    int         flow;    /* 消息流程 */

    enum {
        RESULT_SUCCESS = 0, /* 消息成功 */
        RESULT_FAILED  = 1, /* 消息失败 */
        FLOW_START     = 0, /* 消息开始 */
        FLOW_EXEC      = 1, /* 消息执行 */
        FLOW_FINISH    = 2, /* 消息结束 */
    };

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGResultFlow, id, from, time, message, result, flow);

    static std::optional<MSGResultFlow> FromJsonV1(std::string_view str);
    static std::optional<MSGResultFlow> FromJsonV2(std::string_view str);
    static std::optional<MSGResultFlow> FromJsonV3(std::string_view str);
    static std::optional<MSGResultFlow> FromJsonV4(std::string_view str);
};

/* 实时数据设置命令 */
struct MSGRTimeSetCmd {
    std::string key1;  /* 数据点组 */
    std::string key2;  /* 设备点标签 */
    std::string value; /* 实时值 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGRTimeSetCmd, key1, key2, value);
};

/* 配置数据设置命令 */
struct MSGConfigSetCmd {
    std::string key1;  /* 数据点组 */
    std::string key2;  /* 设备点标签 */
    std::string value; /* 配置值 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGConfigSetCmd, key1, key2, value);
};

/* 控制指令*/
struct MSGCtrlCmd {
    std::string key1;  /* 数据点组 */
    std::string key2;  /* 设备点标签 */
    std::string value; /* 配置值 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGCtrlCmd, key1, key2, value);
};

/* VPN 连接控制指令*/
struct MSGVPNConnectCmd {
    std::string ip;     /* VPN服务器IP */
    int         action; /* VPN连接动作 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGVPNConnectCmd, ip, action);
};

/* 日志消息 */
struct MSGLogMsg {
    std::string level;  /* 日志级别 */
    std::string module; /* 模块名称 */
    std::string msg;    /* 日志内容 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGLogMsg, level, module, msg);
};

/* 调度指令请求 */
struct MSGScheduleCmd {
    std::string key1;   /* 设备组 */
    std::string key2;   /* 设备标签 */
    double      value;  /* 控制值 */
    int         weight; /* 权重 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGScheduleCmd, key1, key2, value, weight);
};

/* 脚本指令请求 */
struct MSGScriptCmd {
    std::string script; /* 脚本 */
    int         weight; /* 权重 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGScriptCmd, script, weight);
};

/* 设置状态请求 */
struct MSGSetStatusCmd {
    enum SysStatus {
        STATUS_INIT    = 0, /* 初始化状态 */
        STATUS_STANDBY = 1, /* 待机状态 */
        STATUS_RUNNING = 2, /* 运行状态 */
        STATUS_DEBUG   = 3, /* 调试状态 */
        STATUS_FAULT   = 4, /* 故障状态 */
    };

    int value; /* 状态值 */
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGSetStatusCmd, value)
};

/* 报警信息推送 */
struct MSGAlarmInfo {

    std::string moduleName;   /* 告警模块 */
    std::string alarmName;    /* 告警名称 */
    int         alarmType;    /* 告警类型 */
    int         alarmLevel;   /* 告警级别 */
    int         alarmStatus;  /* 告警状态 */
    double      alarmValue;   /* 告警值 */
    std::string alarmContent; /* 告警内容 */
    std::string time;         /* 触发时间 */
    std::string resetTime;    /* 复归时间 */
    std::string key1;         /* 告警组 */
    std::string key1Name;     /* 告警组描述 */
    std::string key2;         /* 告警标签 */
    std::string key2Name;     /* 告警标签描述 */
    int         confirm;      /* 确认状态 */
    std::string confirmFrom;  /* 确认用户 */
    std::string confirmTime;  /* 确认时间 */
    std::string confirmDesc;  /* 确认内容 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGAlarmInfo,
                                   moduleName,
                                   alarmName,
                                   alarmType,
                                   alarmLevel,
                                   alarmStatus,
                                   alarmValue,
                                   alarmContent,
                                   time,
                                   resetTime,
                                   key1,
                                   key1Name,
                                   key2,
                                   key2Name,
                                   confirm,
                                   confirmFrom,
                                   confirmTime,
                                   confirmDesc)
};

/* 报警使能请求 */
struct MSGAlarmEnableCmd {
    std::string key1;  /* 告警组 */
    std::string key2;  /* 告警标签 */
    int         type;  /* 更新到文件标志 0: 不更新 1: 更新 */
    int         value; /* 动作  0: 不操作 1: 启用 2: 禁用 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGAlarmEnableCmd, key1, key2, type, value)
};

/* 报警复位请求 */
struct MSGAlarmRecoverCmd {
    std::string key1;  /* 告警组 */
    std::string key2;  /* 告警标签 */
    int         value; /* 动作  0: 不操作 1: 恢复 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGAlarmRecoverCmd, key1, key2, value)
};

/* 报警确认请求 */
struct MSGAlarmConfirmCmd {
    std::string key1;  /* 告警组 */
    std::string key2;  /* 告警标签 */
    std::string from;  /* 确认用户 */
    std::string desc;  /* 确认内容 */
    int         value; /* 动作值  0: 不操作 1: 确认 */

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(MSGAlarmConfirmCmd, key1, key2, from, desc, value)
};

}// namespace helper
