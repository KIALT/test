#include "duration.h"

Duration::Duration() : ns_(0) {}

Duration::Duration(const struct timeval &t) : ns_(t.tv_sec * kSecond + t.tv_usec * kMicrosecond) {}

Duration::Duration(const DurationNano &ns) : ns_(ns.ns) {}

Duration::Duration(const DurationMicro &us) : ns_(us.us * kMicrosecond) {}

Duration::Duration(const DurationMilli &ms) : ns_(ms.ms * kMillisecond) {}

Duration::Duration(const DurationSec &s) : ns_(s.s * kSecond) {}

int64_t Duration::Nanoseconds() const { return ns_; }

int64_t Duration::Microseconds() const { return ns_ / kMicrosecond; }

int64_t Duration::Milliseconds() const { return ns_ / kMillisecond; }

int64_t Duration::Seconds() const { return ns_ / kSecond; }

int64_t Duration::Minutes() const { return ns_ / kMinute; }

int64_t Duration::Hours() const { return ns_ / kHour; }

struct timeval Duration::Timeval() const {
    struct timeval t;
    t.tv_sec  = ns_ / kSecond;
    t.tv_usec = (ns_ % kSecond) / kMicrosecond;
    return t;
}

bool Duration::IsZero() const { return ns_ == 0; }

bool Duration::IsNegative() const { return ns_ < 0; }
bool Duration::operator<(const Duration &rhs) const { return ns_ < rhs.ns_; }

bool Duration::operator<=(const Duration &rhs) const { return ns_ <= rhs.ns_; }

bool Duration::operator>(const Duration &rhs) const { return ns_ > rhs.ns_; }

bool Duration::operator>=(const Duration &rhs) const { return ns_ >= rhs.ns_; }

bool Duration::operator==(const Duration &rhs) const { return ns_ == rhs.ns_; }

Duration Duration::operator+=(const Duration &rhs) {
    ns_ += rhs.ns_;
    return *this;
}

Duration Duration::operator-=(const Duration &rhs) {
    ns_ -= rhs.ns_;
    return *this;
}

Duration Duration::operator*=(int ns) {
    ns_ *= ns;
    return *this;
}

Duration Duration::operator/=(int ns) {
    ns_ /= ns;
    return *this;
}