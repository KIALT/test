#pragma once

#include "singleton.h"

#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <string>

class Logger : public Singleton<Logger>
{
    friend class Singleton<Logger>;
    Logger();

public:
    ~Logger() noexcept override;
    void SetBasicLogger(spdlog::level::level_enum level, const std::string &pattern);
    void SetRotatingLogger(const std::string &file_name, size_t file_size, size_t file_num);
    void Flush();

    template<typename... ARGS>
    static inline void Trace(const char *fmt, const ARGS &...args) {
        Instance().logger_->trace(fmt, args...);
    }

    template<typename... ARGS>
    static inline void Debug(const char *fmt, const ARGS &...args) {
        Instance().logger_->debug(fmt, args...);
    }

    template<typename... ARGS>
    static inline void Info(const char *fmt, const ARGS &...args) {
        Instance().logger_->info(fmt, args...);
    }

    template<typename... ARGS>
    static inline void Warn(const char *fmt, const ARGS &...args) {
        Instance().logger_->warn(fmt, args...);
    }

    template<typename... ARGS>
    static inline void Error(const char *fmt, const ARGS &...args) {
        Instance().logger_->error(fmt, args...);
    }

    template<typename... ARGS>
    static inline void Critical(const char *fmt, const ARGS &...args) {
        Instance().logger_->critical(fmt, args...);
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
    spdlog::level::level_enum       level_;
    std::string                     pattern_;
};
