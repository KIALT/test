#pragma once

#include "modbus_common.h"
#include <cstdint>

class ModbusMapping
{
public:
    ModbusMapping(uint16_t num_bits,
                  uint16_t start_bits,
                  uint16_t num_input_bits,
                  uint16_t start_input_bits,
                  uint16_t num_registers,
                  uint16_t start_registers,
                  uint16_t num_input_registers,
                  uint16_t start_input_registers);

    ~ModbusMapping();

private:
    uint16_t num_bits_;              /*线圈的数量*/
    uint16_t start_bits_;            /*线圈的起始地址*/
    uint16_t num_input_bits_;        /*离散输入的数量*/
    uint16_t start_input_bits_;      /*离散输入的起始地址*/
    uint16_t num_registers_;         /*寄存器的数量*/
    uint16_t start_registers_;       /*寄存器的起始地址*/
    uint16_t num_input_registers_;   /*输入寄存器的数量*/
    uint16_t start_input_registers_; /*输入寄存器的起始地址*/

    uint8_t  *bits_;            /*线圈*/
    uint8_t  *input_bits_;      /*离散输入*/
    uint16_t *registers_;       /*寄存器*/
    uint16_t *input_registers_; /*输入寄存器*/

    bool      CheckBit(uint16_t start, uint16_t num);
    bool      CheckInputBit(uint16_t start, uint16_t num);
    bool      CheckRegister(uint16_t start, uint16_t num);
    bool      CheckInputRegister(uint16_t start, uint16_t num);
    void      SetBit(uint16_t addr, bool value);
    void      SetInputBit(uint16_t addr, bool value);
    void      SetRegister(uint16_t addr, uint16_t value);
    void      SetInputRegister(uint16_t addr, uint16_t value);
    bool      GetBit(uint16_t addr);
    bool      GetInputBit(uint16_t addr);
    uint16_t  GetRegister(uint16_t addr);
    uint16_t  GetInputRegister(uint16_t addr);
    uint8_t  *GetBits() { return bits_; }
    uint8_t  *GetInputBits() { return input_bits_; }
    uint16_t *GetRegisters() { return registers_; }
    uint16_t *GetInputRegisters() { return input_registers_; }
};
