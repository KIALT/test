#include "buffer.h"

Buffer::Buffer(Buffer &&other) noexcept
: buffer_(std::move(other.buffer_)), capacity_(other.capacity_), len_(other.len_), rpos_(other.rpos_),
  wpos_(other.wpos_) {
    other.capacity_ = 0;
    other.len_      = 0;
    other.rpos_     = 0;
    other.wpos_     = 0;
}

Buffer &Buffer::operator=(Buffer &&other) noexcept {
    if (this != &other) {
        buffer_   = std::move(other.buffer_);
        capacity_ = other.capacity_;
        len_      = other.len_;
        rpos_     = other.rpos_;
        wpos_     = other.wpos_;

        other.capacity_ = 0;
        other.len_      = 0;
        other.rpos_     = 0;
        other.wpos_     = 0;
    }
    return *this;
}

void Buffer::Skip(size_t len) { rpos_ = std::min(rpos_ + len, wpos_); }

void Buffer::Retrieve(size_t len) {
    if (len >= ReadableBytes()) {
        Reset();
    } else {
        rpos_ += len;
    }
}

void Buffer::Reset() {
    rpos_ = 0;
    wpos_ = 0;
}

void Buffer::Reserve(size_t len) {
    if (WritableBytes() < len) {
        size_t new_capacity = capacity_ + std::max(len, capacity_);
        auto   new_buffer   = std::make_unique<char[]>(new_capacity);
        std::memcpy(new_buffer.get(), buffer_.get() + rpos_, ReadableBytes());
        buffer_   = std::move(new_buffer);
        capacity_ = new_capacity;
        wpos_ -= rpos_;
        rpos_ = 0;
    }
}

void Buffer::Write(const void *buf, size_t n) {
    if (WritableBytes() < n) {
        Reserve(n);
    }

    std::memcpy(buffer_.get() + wpos_, buf, n);
    wpos_ += n;
    len_ += n;
}

int Buffer::Read(void *buf, size_t n) {
    size_t readable = ReadableBytes();
    size_t nread    = std::min(n, readable);
    std::memcpy(buf, buffer_.get() + rpos_, nread);
    rpos_ += nread;
    return static_cast<int>(nread);
}
