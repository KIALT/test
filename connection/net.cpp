#include "net.h"

#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

namespace net {

void NetConn::Close() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

int NetConn::Send(void *buf, size_t len, int flags) { return ::send(fd_, buf, len, flags); }

int NetConn::Recv(void *buf, size_t len, int flags) { return ::recv(fd_, buf, len, flags); }

int NetConn::SetNonBlock(bool on) {
    int flags = fcntl(fd_, F_GETFL, 0);
    return fcntl(fd_, F_SETFL, flags | (on ? O_NONBLOCK : 0));
}

int NetConn::SetReuseAddr(bool on) {
    int opt = on ? 1 : 0;
    return ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

int NetConn::SetReusePort(bool on) {
    int opt = on ? 1 : 0;
    return ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
}

int NetConn::SetKeepAlive(bool on) {
    int opt = on ? 1 : 0;
    return ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt));
}

void TCPConn::ReCreate() {
    Close();
    fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
}

int TCPConn::SetNoDelay(bool on) {
    int opt = on ? 1 : 0;
    return ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
}

int TCPConn::SetSyncnt(int n) { return ::setsockopt(fd_, IPPROTO_TCP, TCP_SYNCNT, &n, sizeof(n)); }

}// namespace net
