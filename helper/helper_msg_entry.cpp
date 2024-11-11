#include "helper_msg_entry.h"

namespace helper {

std::optional<MSGResultFlow> MSGResultFlow::FromJsonV1(std::string_view str) {
    auto json = nlohmann::json::parse(str);
    return json.get<MSGResultFlow>();
}

std::optional<MSGResultFlow> MSGResultFlow::FromJsonV2(std::string_view str) {
    auto json = nlohmann::json::parse(str);
    return json.get<MSGResultFlow>();
}

std::optional<MSGResultFlow> MSGResultFlow::FromJsonV3(std::string_view str) {
    auto json = nlohmann::json::parse(str);
    return json.get<MSGResultFlow>();
}

std::optional<MSGResultFlow> MSGResultFlow::FromJsonV4(std::string_view str) {
    auto json = nlohmann::json::parse(str);
    return json.get<MSGResultFlow>();
}

}// namespace helper
