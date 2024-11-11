#pragma once

#include <stdint.h>
#include <sys/time.h>

class Duration
{
public:
    static constexpr int64_t kNanosecond  = 1;                   /* 纳秒 */
    static constexpr int64_t kMicrosecond = 1000 * kNanosecond;  /* 微秒 */
    static constexpr int64_t kMillisecond = 1000 * kMicrosecond; /* 毫秒 */
    static constexpr int64_t kSecond      = 1000 * kMillisecond; /* 秒 */
    static constexpr int64_t kMinute      = 60 * kSecond;        /* 分钟 */
    static constexpr int64_t kHour        = 60 * kMinute;        /* 小时 */

    struct DurationNano {
        int64_t ns;
        DurationNano(int64_t nanoseconds) : ns(nanoseconds) {}
    };

    struct DurationMicro {
        int64_t us;
        DurationMicro(int64_t microseconds) : us(microseconds) {}
    };

    struct DurationMilli {
        int64_t ms;
        DurationMilli(int64_t milliseconds) : ms(milliseconds) {}
    };

    struct DurationSec {
        int64_t s;
        DurationSec(int64_t seconds) : s(seconds) {}
    };

    Duration();
    explicit Duration(const struct timeval &t);
    explicit Duration(const DurationNano &ns);
    explicit Duration(const DurationMicro &us);
    explicit Duration(const DurationMilli &ms);
    explicit Duration(const DurationSec &s);

    int64_t Nanoseconds() const;
    int64_t Microseconds() const;
    int64_t Milliseconds() const;
    int64_t Seconds() const;
    int64_t Minutes() const;
    int64_t Hours() const;

    struct timeval Timeval() const;
    bool           IsZero() const;
    bool           IsNegative() const;

    bool     operator<(const Duration &rhs) const;
    bool     operator<=(const Duration &rhs) const;
    bool     operator>(const Duration &rhs) const;
    bool     operator>=(const Duration &rhs) const;
    bool     operator==(const Duration &rhs) const;
    Duration operator+=(const Duration &rhs);
    Duration operator-=(const Duration &rhs);
    Duration operator*=(int ns);
    Duration operator/=(int ns);

private:
    int64_t ns_;
};
