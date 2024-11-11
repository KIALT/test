#pragma once

#include "net.h"
#include <memory>

namespace net {

class UDPConn : public NetConn
{
public:
    UDPConn(const IPAddress &addr);
    virtual ~UDPConn() = default;

    int Bind();
    int SendTo(const void *buf, size_t len, const IPAddress &addr);
    int RecvFrom(void *buf, size_t len, IPAddress &addr);
    int SetBroadcast(bool on);
};

std::shared_ptr<UDPConn> DialUDP(const IPAddress &addr);
std::shared_ptr<UDPConn> ListenUDP(const IPAddress &addr);

}// namespace net
