#pragma once

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>

class Buffer
{
public:
    explicit Buffer(size_t size = kDefaultSize)
    : buffer_(std::make_unique<char[]>(size)), capacity_(size), len_(0), rpos_(0), wpos_(0) {}

    ~Buffer()                         = default;
    Buffer(const Buffer &)            = delete;
    Buffer &operator=(const Buffer &) = delete;

    Buffer(Buffer &&other) noexcept;
    Buffer &operator=(Buffer &&other) noexcept;

    void   Skip(size_t len);
    void   Retrieve(size_t len);
    void   Write(const void *buf, size_t n);
    int    Read(void *buf, size_t n);
    void   Reset();
    void   Reserve(size_t len);
    void   Append(const void *buf, size_t n) { Write(buf, n); }
    void   Append(const std::string &s) { Write(s.data(), s.size()); }
    size_t WritableBytes() const { return capacity_ - wpos_; }
    size_t ReadableBytes() const { return wpos_ - rpos_; }

    char  *data() { return buffer_.get() + rpos_; }
    size_t length() const { return wpos_ - rpos_; }
    size_t capacity() const { return capacity_; }

private:
    static constexpr size_t kDefaultSize = 1024;

    std::unique_ptr<char[]> buffer_;
    size_t                  capacity_;
    size_t                  len_;
    size_t                  rpos_;
    size_t                  wpos_;
};
