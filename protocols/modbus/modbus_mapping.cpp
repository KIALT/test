#pragma once

#include "modbus_mapping.h"
#include <cstring>

ModbusMapping::ModbusMapping(uint16_t num_bits,
                             uint16_t start_bits,
                             uint16_t num_input_bits,
                             uint16_t start_input_bits,
                             uint16_t num_registers,
                             uint16_t start_registers,
                             uint16_t num_input_registers,
                             uint16_t start_input_registers) {

    num_bits_              = num_bits;
    start_bits_            = start_bits;
    num_input_bits_        = num_input_bits;
    start_input_bits_      = start_input_bits;
    num_registers_         = num_registers;
    start_registers_       = start_registers;
    num_input_registers_   = num_input_registers;
    start_input_registers_ = start_input_registers;

    bits_            = new uint8_t[num_bits_];
    input_bits_      = new uint8_t[num_input_bits_];
    registers_       = new uint16_t[num_registers_];
    input_registers_ = new uint16_t[num_input_registers_];

    memset(bits_, 0, num_bits_);
    memset(input_bits_, 0, num_input_bits_);
    memset(registers_, 0, num_registers_);
    memset(input_registers_, 0, num_input_registers_);
}

ModbusMapping::~ModbusMapping() {
    delete[] bits_;
    delete[] input_bits_;
    delete[] registers_;
    delete[] input_registers_;
}

bool ModbusMapping::CheckBit(uint16_t start, uint16_t num) {
    return start >= start_bits_ && start + num <= start_bits_ + num_bits_;
}

bool ModbusMapping::CheckInputBit(uint16_t start, uint16_t num) {
    return start >= start_input_bits_ && start + num <= start_input_bits_ + num_input_bits_;
}

bool ModbusMapping::CheckRegister(uint16_t start, uint16_t num) {
    return start >= start_registers_ && start + num <= start_registers_ + num_registers_;
}

bool ModbusMapping::CheckInputRegister(uint16_t start, uint16_t num) {
    return start >= start_input_registers_ && start + num <= start_input_registers_ + num_input_registers_;
}

void ModbusMapping::SetBit(uint16_t addr, bool value) { bits_[addr - start_bits_] = value; }

void ModbusMapping::SetInputBit(uint16_t addr, bool value) { input_bits_[addr - start_input_bits_] = value; }

void ModbusMapping::SetRegister(uint16_t addr, uint16_t value) { registers_[addr - start_registers_] = value; }

void ModbusMapping::SetInputRegister(uint16_t addr, uint16_t value) {
    input_registers_[addr - start_input_registers_] = value;
}

bool ModbusMapping::GetBit(uint16_t addr) { return bits_[addr - start_bits_]; }

bool ModbusMapping::GetInputBit(uint16_t addr) { return input_bits_[addr - start_input_bits_]; }

uint16_t ModbusMapping::GetRegister(uint16_t addr) { return registers_[addr - start_registers_]; }

uint16_t ModbusMapping::GetInputRegister(uint16_t addr) { return input_registers_[addr - start_input_registers_]; }
