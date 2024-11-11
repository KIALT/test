#pragma once

#include <cstdint>

#define MODBUS_MAX_READ_REGISTERS     125  /* Modbus 最大读寄存器数 */
#define MODBUS_MAX_WRITE_REGISTERS    123  /* Modbus 最大写寄存器数 */
#define MODBUS_MAX_WR_WRITE_REGISTERS 121  /* Modbus 最大写读写寄存器数 */
#define MODBUS_MAX_WR_READ_REGISTERS  125  /* Modbus 最大写读读寄存器数 */
#define MODBUS_MAX_ADU_LENGTH         260  /* Modbus 最大的ADU长度 */
#define MODBUS_MAX_PDU_LENGTH         253  /* Modbus 最大的PDU长度 */
#define MODBUS_EXCEPTION_LENGTH       5    /* Modbus 异常长度 */
#define MODBUS_EXCEPTION_FLAG         0x80 /* Modbus 异常标志 */
#define MODBUS_MAX_READ_BITS          2000 /* Modbus 最大读线圈数 */
#define MODBUS_MAX_WRITE_BITS         1968 /* Modbus 最大写线圈数 */
#define MODBUS_MAX_READ_REGISTERS     125  /* Modbus 最大读寄存器数 */
#define MODBUS_MAX_WRITE_REGISTERS    123  /* Modbus 最大写寄存器数 */
#define MODBUS_MAX_WR_WRITE_REGISTERS 121  /* Modbus 最大写读写寄存器数 */
#define MODBUS_MAX_WR_READ_REGISTERS  125  /* Modbus 最大写读读寄存器数 */
#define MODBUS_TCP_HEADER_LENGTH      6    /* Modbus TCP 头长度 */
#define MODBUS_RTU_HEADER_LENGTH      1    /* Modbus RTU 头长度 */

enum ModbusFunctionEnum {
    FC_READ_COILS                    = 0x01, /* 读线圈 */
    FC_READ_DISCRETE_INPUTS          = 0x02, /* 读离散输入 */
    FC_READ_HOLDING_REGISTERS        = 0x03, /* 读保持寄存器 */
    FC_READ_INPUT_REGISTERS          = 0x04, /* 读输入寄存器 */
    FC_WRITE_SINGLE_COIL             = 0x05, /* 写单个线圈 */
    FC_WRITE_SINGLE_REGISTER         = 0x06, /* 写单个寄存器 */
    FC_READ_EXCEPTION_STATUS         = 0x07, /* 读异常状态 */
    FC_WRITE_MULTIPLE_COILS          = 0x0F, /* 写多个线圈 */
    FC_WRITE_MULTIPLE_REGISTERS      = 0x10, /* 写多个寄存器 */
    FC_REPORT_SLAVE_ID               = 0x11, /* 读从机ID */
    FC_READ_FILE_RECORD              = 0x14, /* 读文件记录 */
    FC_WRITE_FILE_RECORD             = 0x15, /* 写文件记录 */
    FC_MASK_WRITE_REGISTER           = 0x16, /* 屏蔽写寄存器 */
    FC_READ_WRITE_MULTIPLE_REGISTERS = 0x17, /* 读写多个寄存器 */
};

enum ModbusExceptionEnum {
    EC_NONE                 = 0x00, /* 无异常 */
    EC_ILLEGAL_FUNCTION     = 0x01, /* 非法功能 */
    EC_ILLEGAL_DATA_ADDR    = 0x02, /* 非法数据地址 */
    EC_ILLEGAL_DATA_VALUE   = 0x03, /* 非法数据值 */
    EC_SLAVE_DEVICE_FAILURE = 0x04, /* 从机设备故障 */
    EC_ACKNOWLEDGE          = 0x05, /* 确认 */
    EC_SLAVE_DEVICE_BUSY    = 0x06, /* 从机设备忙 */
    EC_MEMORY_PARITY_ERROR  = 0x08, /* 存储奇偶校验错误 */
    EC_GATEWAY_PATH_FAILED  = 0x0A, /* 网关路径失败 */
    EC_GATEWAY_TGT_FAILED   = 0x0B, /* 网关目标设备响应失败 */
    EC_INVALID_REQUEST      = 0x80, /* 无效的请求 */
};

enum ModbusAreaEnum {
    kAreaCoils            = 1, /* 线圈 */
    kAreaDiscreteInputs   = 2, /* 离散输入 */
    kAreaHoldingRegisters = 3, /* 保持寄存器 */
    kAreaInputRegisters   = 4, /* 输入寄存器 */
};

enum ModbusProtocolEnum {
    kProtocolRTU = 0, /* Modbus RTU */
    kProtocolTCP = 1, /* Modbus TCP */
};

struct ModbusTCPHeader {
    uint16_t tid;      /* 事务ID */
    uint16_t protocol; /* 协议ID */
    uint16_t len;      /* 长度 */
} __attribute__((packed));
