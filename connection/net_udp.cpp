#include "net_udp.h"

namespace net {

UDPConn::UDPConn(const IPAddress &addr) : NetConn(addr) {}

int UDPConn::Bind() {
    struct sockaddr_in addr = addr_.addr;
    return ::bind(fd_, (struct sockaddr *) &addr, sizeof(addr));
}

int UDPConn::SendTo(const void *buf, size_t len, const IPAddress &addr) {
    return ::sendto(fd_, buf, len, 0, (struct sockaddr *) &addr.addr, sizeof(addr.addr));
}

int UDPConn::RecvFrom(void *buf, size_t len, IPAddress &addr) {
    socklen_t addr_len = sizeof(addr.addr);
    return ::recvfrom(fd_, buf, len, 0, (struct sockaddr *) &addr.addr, &addr_len);
}

int UDPConn::SetBroadcast(bool on) {
    int opt = on ? 1 : 0;
    return ::setsockopt(fd_, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
}

std::shared_ptr<UDPConn> DialUDP(const IPAddress &addr) {
    auto conn = std::make_shared<UDPConn>(addr);
    return conn;
}

std::shared_ptr<UDPConn> ListenUDP(const IPAddress &addr) {
    auto conn = std::make_shared<UDPConn>(addr);
    if (conn->Bind() < 0) {
        return nullptr;
    }
    return conn;
}

}// namespace net
