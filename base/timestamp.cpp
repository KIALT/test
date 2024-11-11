#include "timestamp.h"

#include <chrono>
#include <cstdint>
#include <ctime>

using std::chrono::duration_cast;
using std::chrono::system_clock;

Timestamp::Timestamp() : tp_(system_clock::now()) {}

Timestamp::Timestamp(const system_clock::time_point &tp) : tp_(tp) {}

Timestamp::Timestamp(int64_t nanoseconds)
: tp_(std::chrono::system_clock::time_point(std::chrono::nanoseconds(nanoseconds))) {}

Timestamp::Timestamp(struct timeval &tv)
: tp_(std::chrono::system_clock::time_point(std::chrono::seconds(tv.tv_sec) + std::chrono::microseconds(tv.tv_usec))) {}

Timestamp::Timestamp(struct tm &tm) : tp_(std::chrono::system_clock::time_point(std::chrono::seconds(mktime(&tm)))) {}

const char *Timestamp::Format(const char *format) const {
    static char buf[64];
    strftime(buf, sizeof(buf), format, LocalTime());
    return buf;
}

void Timestamp::Update() { tp_ = std::chrono::system_clock::now(); }

struct tm *Timestamp::LocalTime() const {
    time_t t = system_clock::to_time_t(tp_);
    return localtime(&t);
}

struct timeval Timestamp::Timeval() const {

    struct timeval tv;
    tv.tv_sec  = duration_cast<std::chrono::seconds>(tp_.time_since_epoch()).count();
    tv.tv_usec = duration_cast<std::chrono::microseconds>(tp_.time_since_epoch()).count() % 1000000;
    return tv;
}

int64_t Timestamp::Nanoseconds() const {
    return duration_cast<std::chrono::nanoseconds>(tp_.time_since_epoch()).count();
}
int64_t Timestamp::Microseconds() const {
    return duration_cast<std::chrono::microseconds>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::Milliseconds() const {
    return duration_cast<std::chrono::milliseconds>(tp_.time_since_epoch()).count();
}

int64_t Timestamp::Seconds() const { return duration_cast<std::chrono::seconds>(tp_.time_since_epoch()).count(); }

bool Timestamp::operator<(const Timestamp &rhs) const { return tp_ < rhs.tp_; }

bool Timestamp::operator<=(const Timestamp &rhs) const { return tp_ <= rhs.tp_; }

bool Timestamp::operator>(const Timestamp &rhs) const { return tp_ > rhs.tp_; }

bool Timestamp::operator>=(const Timestamp &rhs) const { return tp_ >= rhs.tp_; }

bool Timestamp::operator==(const Timestamp &rhs) const { return tp_ == rhs.tp_; }

int64_t Timestamp::operator-(const Timestamp &rhs) const {
    return duration_cast<std::chrono::milliseconds>(tp_ - rhs.tp_).count();
}
