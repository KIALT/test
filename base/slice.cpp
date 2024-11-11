#include "slice.h"

#include <string>

int Slice::Compare(const Slice &b) const {
    const size_t min_len = (size_ < b.size_) ? size_ : b.size_;
    int          r       = memcmp(data_, b.data_, min_len);
    if (r == 0) {
        if (size_ < b.size_)
            r = -1;
        else if (size_ > b.size_)
            r = +1;
    }
    return r;
}

char toHex(unsigned char v) {
    if (v <= 9) {
        return '0' + v;
    }
    return 'A' + v - 10;
}

std::string Slice::ToString(bool hex) const {

    std::string result;
    if (hex) {
        result.reserve(size_ * 2);
        for (size_t i = 0; i < size_; i++) {
            unsigned char c = data_[i];
            result.push_back(toHex(c >> 4));
            result.push_back(toHex(c & 0x0f));
        }
    } else {
        result.assign(data_, size_);
    }
    return result;
}