#pragma once

#include <string>
#include <string_view>


class RedisObject
{
public:
    std::string group_; /* 数据组 */
    std::string tag_;   /* 数据标签 */

    RedisObject() = default;
    RedisObject(std::string_view group, std::string_view tag): group_(group), tag_(tag) {}

    virtual ~RedisObject() = default;
    virtual std::string_view Serialize() const = 0;
    virtual bool             Deserialize(std::string_view str) = 0;
};


class RedisRealObject : public RedisObject
{
public:
    int         vaild_;  /* 是否有效 */
    double      value_;  /* 值 */
    std::string time_;  /* 时间 */

    virtual ~RedisRealObject() = default;
    std::string_view Serialize() const override;
    bool             Deserialize(std::string_view str) override;
};


class RedisConfigObject : public RedisObject
{
public:
    std::string value_;

    virtual ~RedisConfigObject() = default;
    std::string_view Serialize() const override;
    bool             Deserialize(std::string_view str) override;
};


class RedisAlarmObject : public RedisObject
{
public:
    std::string_view alarm_type_;
    std::string_view alarm_level_;
    std::string_view alarm_message_;

    virtual ~RedisAlarmObject() = default;
    std::string_view Serialize() const override;
    bool             Deserialize(std::string_view str) override;
};
