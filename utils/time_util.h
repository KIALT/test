#pragma once


#include <string>
#include <chrono>
#include <sys/time.h>
#include <string_view>

namespace time_util {

inline int64_t GetCurrentTimestamp()  
{
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline int64_t GetCurrentTimestampMs()  
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline int64_t GetCurrentTimestampUs()  
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline std::string FormatTimestamp(int64_t t, std::string_view format = "%Y-%m-%d %H:%M:%S")
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    time_t now = tv.tv_sec;
    tm local_time = *localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), format.data(), &local_time);
    return std::string(buffer);
}

}
