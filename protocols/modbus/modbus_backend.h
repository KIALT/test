#pragma once

#include "modbus_common.h"
#include <cstddef>
#include <cstdint>

union ModbusSft
{
    uint8_t data[6];
    struct {
        uint16_t tid;
        uint16_t proto;
        uint16_t len;
    } tcp;
};

class ModbusBackend
{
public:
    ModbusBackend()          = default;
    virtual ~ModbusBackend() = default;

    virtual bool   Connect()                                              = 0;
    virtual void   Close()                                                = 0;
    virtual bool   IsConnected()                                          = 0;
    virtual int    Read(uint8_t *buffer, size_t length)                   = 0;
    virtual int    Write(const uint8_t *buffer, size_t length)            = 0;
    virtual int    Decode(ModbusSft *sft, uint8_t *buffer, size_t length) = 0;
    virtual int    Encode(ModbusSft *sft, uint8_t *buffer, size_t length) = 0;
    virtual size_t GetHeaderLength()                                      = 0;

protected:
    ModbusSft sft_;
    int       header_length_;
};
