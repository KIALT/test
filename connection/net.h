#pragma once

#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <string>

namespace net {

struct IPAddress {
    std::string        ip;
    uint16_t           port;
    struct sockaddr_in addr;

    IPAddress() : port(0) {}
    IPAddress(const std::string& ip_, uint16_t port_) : ip(ip_), port(port_) {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
};

inline std::string IPAddrToString(const IPAddress &addr) { return addr.ip + ":" + std::to_string(addr.port); }

inline IPAddress StringToIPAddr(const std::string &str) {
    auto pos = str.find(":");
    return IPAddress{str.substr(0, pos), static_cast<uint16_t>(std::stoi(str.substr(pos + 1)))};
}

inline IPAddress IPAddrResolve(const std::string &ip, uint16_t port) {
    IPAddress addr;
    addr.ip                   = ip;
    addr.port                 = port;
    addr.addr.sin_family      = AF_INET;
    addr.addr.sin_port        = htons(port);
    addr.addr.sin_addr.s_addr = inet_addr(ip.c_str());
    return addr;
}

inline IPAddress IPAddrAny(uint16_t port) {
    IPAddress addr;
    addr.ip                   = "0.0.0.0";
    addr.port                 = port;
    addr.addr.sin_family      = AF_INET;
    addr.addr.sin_port        = htons(port);
    addr.addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}

class IPAddressHash
{
public:
    size_t operator()(const IPAddress &addr) const { return std::hash<std::string>()(addr.ip); }
};

class IPAddressEqual
{
public:
    bool operator()(const IPAddress &lhs, const IPAddress &rhs) const { return lhs.ip == rhs.ip; }
};

class NetConn
{
public:
    NetConn(const IPAddress &addr) : addr_(addr), fd_(-1) {}
    virtual ~NetConn() { Close(); };

    NetConn(const NetConn&) = delete ;   
    NetConn& operator=(const NetConn&) = delete;

    void      Close();
    int       Send(void *buf, size_t len, int flags);
    int       Recv(void *buf, size_t len, int flags);
    int       SetNonBlock(bool on);
    int       SetReuseAddr(bool on);
    int       SetReusePort(bool on);
    int       SetKeepAlive(bool on);
    int       GetFd() const { return fd_; }
    IPAddress GetAddr() const { return addr_; }

protected:
    IPAddress addr_;
    int       fd_;
};

class TCPConn : public NetConn
{
public:
    TCPConn(const IPAddress &addr) : NetConn(addr) { fd_ = ::socket(AF_INET, SOCK_STREAM, 0); }

    void ReCreate();
    int  SetNoDelay(bool on);
    int  SetSyncnt(int n);
    bool IsConnected() const { return connected; }

protected:
    bool connected = false;
};

}// namespace net
