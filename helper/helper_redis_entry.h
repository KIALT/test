#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace helper {

struct RedisObject {
    RedisObject()          = default;
    virtual ~RedisObject() = default;

    virtual double GetValue() const = 0;
};

struct RedisRealObject : RedisObject {
    int         valid; /* 有效标志 */
    double      value; /* 数据值 */
    std::string time;  /* 数据时间 */

    double GetValue() const override;
};

struct RedisConfigObject : RedisObject {
    std::string value; /* 数据值 */
    double      GetValue() const override;
};

struct RedisAlarmObject : RedisObject {
    std::string value; /* 数据值 */
    double      GetValue() const override;
};

}// namespace helper
