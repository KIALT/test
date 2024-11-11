#include "net_tcp.h"

namespace net {

bool TCPStream::Connect() {
    if (!connected) {
        struct sockaddr_in addr = addr_.addr;
        socklen_t          len  = sizeof(addr);
        return ::connect(fd_, (struct sockaddr *) &addr, sizeof(addr));
    }
    return true;
}

int TCPListener::Listen(int backlog) {

    SetReuseAddr(true);

    struct sockaddr_in addr = addr_.addr;
    socklen_t          len  = sizeof(addr);
    if (::bind(fd_, (struct sockaddr *) &addr, len) < 0) {
        return -1;
    }

    return ::listen(fd_, backlog);
}

std::shared_ptr<TCPStream> TCPListener::Accept() {
    struct sockaddr_in addr;
    socklen_t          len = sizeof(addr);
    int                fd  = ::accept(fd_, (struct sockaddr *) &addr, &len);
    if (fd < 0) {
        return nullptr;
    }
    return std::make_shared<TCPStream>(addr);
}

std::shared_ptr<TCPStream> Dial(const IPAddress &addr) {
    auto stream = std::make_shared<TCPStream>(addr);
    if (stream->Connect()) {
        return stream;
    }
    return nullptr;
}

std::shared_ptr<TCPListener> Listen(const IPAddress &addr, int backlog) {
    auto listener = std::make_shared<TCPListener>(addr);
    if (listener->Listen(backlog) < 0) {
        return nullptr;
    }
    return listener;
}

}// namespace net
