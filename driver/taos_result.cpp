#include "taos_result.h"
#include <string>

std::string TAOSValue::AsTimestamp() const {
    char   buf[32];
    time_t t = *(time_t *) value_ / 1000;
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return std::string(buf);
}

TAOSResult::TAOSResult(TAOS_RES *res) : res_(res, [](TAOS_RES *r) { taos_free_result(r); }) {}

TAOSResult::TAOSResult(TAOSResult &&other) noexcept : res_(std::move(other.res_)) {}

TAOSResult &TAOSResult::operator=(TAOSResult &&other) noexcept {
    res_ = std::move(other.res_);
    return *this;
}
