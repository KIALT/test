#pragma once

#include <chrono>
#include <cstdint>

class Timestamp
{
public:
    Timestamp();
    explicit Timestamp(const std::chrono::system_clock::time_point &tp);
    explicit Timestamp(int64_t nanoseconds);
    explicit Timestamp(struct timeval &tv);
    explicit Timestamp(struct tm &tm);

    static Timestamp Now() { return Timestamp(std::chrono::system_clock::now()); }
    const char      *Format(const char *format = "%Y-%m-%d %H:%M:%S") const;
    void             Update();
    struct tm       *LocalTime() const;
    struct timeval   Timeval() const;
    int64_t          Nanoseconds() const;
    int64_t          Microseconds() const;
    int64_t          Milliseconds() const;
    int64_t          Seconds() const;

    bool    operator<(const Timestamp &rhs) const;
    bool    operator<=(const Timestamp &rhs) const;
    bool    operator>(const Timestamp &rhs) const;
    bool    operator>=(const Timestamp &rhs) const;
    bool    operator==(const Timestamp &rhs) const;
    int64_t operator-(const Timestamp &rhs) const;

private:
    std::chrono::system_clock::time_point tp_;
};
