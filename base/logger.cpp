#include "logger.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger() {
    logger_  = spdlog::stdout_color_mt("consloe", spdlog::color_mode::always);
    level_   = spdlog::level::debug;
    pattern_ = "[tid:%t] [%Y-%m-%d %H:%M:%S] [%^%l%$] %v";

    logger_->set_level(level_);
    logger_->set_pattern(pattern_);

    spdlog::set_default_logger(logger_);
    spdlog::flush_every(std::chrono::seconds(10));
}

Logger::~Logger() noexcept { spdlog::drop_all(); }
void Logger::SetBasicLogger(spdlog::level::level_enum level, const std::string &pattern) {

    level_   = level;
    pattern_ = pattern;

    logger_->set_level(level_);
    logger_->set_pattern(pattern_);
}

void Logger::SetRotatingLogger(const std::string &file_name, size_t file_size, size_t file_num) {
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, file_size, file_num);
    rotating_sink->set_level(level_);
    rotating_sink->set_pattern(pattern_);
    logger_->sinks().push_back(rotating_sink);
}

void Logger::Flush() { logger_->flush(); }