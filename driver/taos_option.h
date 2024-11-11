#pragma once

#include <string>

struct TAOSOption {
    std::string host;
    int         port;
    std::string user;
    std::string password;

    TAOSOption() : port(6030) {}
    TAOSOption(std::string_view host, int port, std::string_view user, std::string_view password)
    : host(host), port(port), user(user), password(password) {}
};
