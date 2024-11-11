#pragma once

#include <linux/can.h>
#include <string>   

class SocketCan
{
public:
    explicit SocketCan(const std::string &dev, int baudrate);
    ~SocketCan();

    bool Connect();
    void Close();
    int  Read(void *buf, int n, int flags);
    int  Read(struct can_frame *frame);
    int  Write(const void *buf, int n, int flags);
    int  Write(const struct can_frame *frame);
    int  SetFilter(uint32_t id, uint32_t mask) const;
    void SetBaudrate(int baudrate);

private:
    std::string dev_;
    int         baudrate_;
    int         sock_;
};
