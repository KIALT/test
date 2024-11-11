#pragma once

#include <algorithm>
#include <string>
#include <cstdarg>
#include <vector>
#include <sstream>

namespace string_util {

inline std::string Format(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    va_list args_copy;
    va_copy(args_copy, args);
    const int len = vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);
    
    if (len < 0) return std::string();
    
    std::vector<char> buffer(len + 1);
    vsnprintf(buffer.data(), buffer.size(), format, args);
    va_end(args);
    
    return std::string(buffer.data(), len);
}

inline std::string ToLower(const std::string &str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

inline std::string ToUpper(const std::string &str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

inline std::string Trim(const std::string &str) {
    std::string result = str;
    result.erase(result.begin(),
                 std::find_if(result.begin(), result.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    result.erase(
        std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
        result.end());
    return result;
}

inline std::string LTrim(const std::string &str) {
    std::string result = str;
    result.erase(result.begin(),
                 std::find_if(result.begin(), result.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return result;
}

inline std::string RTrim(const std::string &str) {
    std::string result = str;
    result.erase(
        std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
        result.end());
    return result;
}

inline bool StartsWith(const std::string &str, const std::string &prefix, bool case_sensitive = true) {
    if (str.length() < prefix.length()) return false;
    
    if (case_sensitive) {
        return str.compare(0, prefix.length(), prefix) == 0;
    }
    return ToLower(str.substr(0, prefix.length())) == ToLower(prefix);
}

inline bool EndsWith(const std::string &str, const std::string &suffix, bool case_sensitive = true) {
    if (str.length() < suffix.length()) return false;
    
    if (case_sensitive) {
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    }
    return ToLower(str.substr(str.length() - suffix.length())) == ToLower(suffix);
}

inline std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

inline std::string Join(const std::vector<std::string>& strings, const std::string& delimiter) {
    if (strings.empty()) return "";
    
    std::stringstream ss;
    ss << strings[0];
    for (size_t i = 1; i < strings.size(); ++i) {
        ss << delimiter << strings[i];
    }
    return ss.str();
}

inline std::string Replace(std::string str, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

}// namespace string_util
