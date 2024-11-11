#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <zlib.h>

class GzipUtil
{
public:
    static bool Compress(const char *data, size_t length, std::string &compressed, int level = Z_DEFAULT_COMPRESSION) {
        return true;
    };
    static bool Decompress(const char *data, size_t length, std::string &decompressed) { return true; };
};
