#pragma once

#include "net.h"
#include <memory>
#include <sys/socket.h>

namespace net {

class TCPStream : public TCPConn
{
public:
    TCPStream(const IPAddress &addr);

    bool Connect();

    
};

class TCPListener : public TCPConn
{

public:
    TCPListener(const IPAddress &addr);

    int                        Listen(int backlog = 32);
    std::shared_ptr<TCPStream> Accept();
};

std::shared_ptr<TCPStream>   Dial(const IPAddress &addr);
std::shared_ptr<TCPListener> Listen(const IPAddress &addr, int backlog = 32);

};// namespace net