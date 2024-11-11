#pragma once

#include <arpa/inet.h>
#include <cstdint>

namespace endian {

static inline uint16_t SwapEndian16(uint16_t val) { return htons(val); }

static inline uint32_t SwapEndian32(uint32_t val) { return htonl(val); }

static inline uint64_t SwapEndian64(uint64_t val) {
    uint32_t high = htonl(val >> 32);
    uint32_t low  = htonl(val & 0xFFFFFFFF);
    return (static_cast<uint64_t>(high) << 32) | low;
}

static inline uint16_t ToNetwork16(uint16_t val) { return SwapEndian16(val); }

static inline uint32_t ToNetwork32(uint32_t val) { return SwapEndian32(val); }

static inline uint64_t ToNetwork64(uint64_t val) { return SwapEndian64(val); }

};// namespace endian
