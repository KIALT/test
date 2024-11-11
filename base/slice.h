#pragma once

#include <cassert>
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>

class Slice
{
public:
    Slice() = default;
    Slice(const char *d, size_t n) : data_(d), size_(n) {}
    Slice(const std::string &s) : data_(s.data()), size_(s.size()) {}
    Slice(const std::string_view &sv) : data_(sv.data()), size_(sv.size()) {}
    Slice(const char *s) : data_(s), size_(strlen(s)) {}

    void Clear() {
        data_ = "";
        size_ = 0;
    }

    void RemovePrefix(size_t n) {
        assert(n <= size());
        data_ += n;
        size_ -= n;
    }

    void RemoveSuffix(size_t n) {
        assert(n <= size());
        size_ -= n;
    }

    bool StartsWith(const Slice &x) const { return ((size_ >= x.size_) && (memcmp(data_, x.data_, x.size_) == 0)); }

    bool EndsWith(const Slice &x) const {
        return ((size_ >= x.size_) && (memcmp(data_ + (size_ - x.size_), x.data_, x.size_) == 0));
    }

    int              Compare(const Slice &b) const;
    std::string      ToString(bool hex = false) const;
    std::string_view ToStringView() const { return std::string_view(data_, size_); }

    const char *data() const { return data_; }
    size_t      size() const { return size_; }
    bool        empty() const { return size_ == 0; }

    char operator[](size_t n) const {
        assert(n < size());
        return data_[n];
    }

private:
    const char *data_;
    size_t      size_;
};

inline bool operator==(const Slice &x, const Slice &y) {
    return ((x.size() == y.size()) && (memcmp(x.data(), y.data(), x.size()) == 0));
}

inline bool operator!=(const Slice &x, const Slice &y) { return !(x == y); }
