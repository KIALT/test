#pragma once

#include "singleton.h"

#include <cstdint>
#include <stdint.h>
#include <sys/time.h>

struct SnowFlakeID64 {
    union
    {
        struct {
            uint64_t seq  : 12; /* 12  序列号 */
            uint64_t wid  : 6;  /* 6   工作机器ID */
            uint64_t did  : 4;  /* 4   数据中心ID */
            uint64_t time : 41; /* 41  时间戳 */
            uint64_t sign : 1;  /* 1   符号位 */
        };
        uint64_t id;
    };

    SnowFlakeID64() = default;
    SnowFlakeID64(uint64_t seq, uint64_t wid, uint64_t did, uint64_t time, uint64_t sign)
    : seq(seq), wid(wid), did(did), time(time), sign(sign) {}
};

struct SnowFlakeID32 {
    union
    {
        struct {
            uint32_t seq  : 8;  /* 8   序列号 */
            uint32_t role : 4;  /* 4   角色ID */
            uint32_t time : 19; /* 19  时间戳 */
            uint32_t sign : 1;  /* 1   符号位 */
        };
        uint32_t id;
    };

    SnowFlakeID32() = default;
    SnowFlakeID32(uint32_t seq, uint32_t role, uint32_t time, uint32_t sign)
    : seq(seq), role(role), time(time), sign(sign) {}
};

class Snowflake : public Singleton<Snowflake>
{
    friend class Singleton<Snowflake>;
    Snowflake() : seq_(0), wid_(0), did_(0), role_(0) {}

public:
    ~Snowflake() override = default;
    static void     Init(int wid, int did, int role);
    static uint64_t Generate64();
    static uint32_t Generate32();

private:
    uint64_t seq_;  /* 序列号 */
    int      wid_;  /* 工作机器ID */
    int      did_;  /* 数据中心ID */
    int      role_; /* 角色ID */

    static uint64_t GetTime();
};

inline uint64_t Snowflake::GetTime() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return (uint64_t) tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

inline uint64_t Snowflake::Generate64() {

    auto &self = Snowflake::Instance();
    self.seq_  = (self.seq_ + 1) & 0xFFF;

    SnowFlakeID64 id(self.seq_, self.wid_, self.did_, GetTime(), 0);
    return id.id;
}

inline uint32_t Snowflake::Generate32() {
    auto &self = Snowflake::Instance();
    self.seq_  = (self.seq_ + 1) & (UINT8_MAX - 1);

    SnowFlakeID32 id(self.seq_, self.role_, self.wid_, GetTime());
    return id.id;
}
