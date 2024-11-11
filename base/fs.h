#pragma once

#include <string>
#include <string_view>
#include <sys/stat.h>

namespace fs {

inline time_t GetFileModifyTime(std::string_view path) {
    struct stat file_stat;
    if (stat(path.data(), &file_stat) != 0) {
        return 0;
    }
    return file_stat.st_mtime;
}

}// namespace fs
