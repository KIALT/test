#include "redis_object.h"

#include <cstdio>
#include <cstdlib>

std::string_view RedisRealObject::Serialize() const
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "{\"vaild\":\"%d\",\"value\":\"%lf\",\"time\":\"%s\"}", vaild_, value_, time_.c_str());
    return std::string_view(buf);
}

bool RedisRealObject::Deserialize(std::string_view str)
{
    if (str.empty())
        return false;

    int mask_idx[12] = {0};
    int mask_cnt = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '"') {
            mask_idx[mask_cnt++] = i;
        }
    }

    if (mask_cnt != 12)
        return false;

    vaild_ = std::atoi(str.data() + mask_idx[2] + 1);
    value_ = std::atof(str.data() + mask_idx[6] + 1);
    time_ = std::string(str.data() + mask_idx[10] + 1, mask_idx[11] - mask_idx[10] - 1);

    return true;
}


std::string_view RedisConfigObject::Serialize() const
{
    return value_;
}

bool RedisConfigObject::Deserialize(std::string_view str)
{
    if (str.empty())
        return false;

    value_ = str;
    return true;
}



std::string_view RedisAlarmObject::Serialize() const
{
    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "{\"alarm_type\":\"%s\",\"alarm_level\":\"%s\",\"alarm_message\":\"%s\"}", alarm_type_.data(), alarm_level_.data(), alarm_message_.data());
    return std::string_view(buf);
}


bool RedisAlarmObject::Deserialize(std::string_view str)
{
    if (str.empty())
        return false;

    return true;
}
