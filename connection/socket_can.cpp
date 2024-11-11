#pragma once

#include "socket_can.h"
#include <cstring>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

SocketCan::SocketCan(const std::string &dev, int baudrate) : dev_(dev), baudrate_(baudrate), sock_(-1) {}

SocketCan::~SocketCan() { Close(); }

bool SocketCan::Connect() {
    sock_ = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sock_ < 0) {
        return false;
    }

    struct ifreq ifr;
    strcpy(ifr.ifr_name, dev_.c_str());
    if (::ioctl(sock_, SIOCGIFINDEX, &ifr) < 0) {
        return false;
    }

    struct sockaddr_can addr;
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    return ::bind(sock_, (struct sockaddr *) &addr, sizeof(addr)) == 0;
}

void SocketCan::Close() {
    if (sock_ >= 0) {
        ::close(sock_);
    }
}

int SocketCan::Read(struct can_frame *frame) { return ::recv(sock_, frame, sizeof(struct can_frame), 0); }

int SocketCan::Read(void *buf, int n, int flags) { return ::recv(sock_, buf, n, flags); }

int SocketCan::Write(const void *buf, int n, int flags) { return ::send(sock_, buf, n, flags); }

int SocketCan::Write(const struct can_frame *frame) { return ::send(sock_, frame, sizeof(struct can_frame), 0); }

int SocketCan::SetFilter(uint32_t id, uint32_t mask) const {
    struct can_filter rfilter[1];
    rfilter[0].can_id   = id;
    rfilter[0].can_mask = mask;
    return ::setsockopt(sock_, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
}

void SocketCan::SetBaudrate(int baudrate) {
    std::string shut_down_cmd     = "ip link set " + dev_ + " down";
    std::string set_baud_rate_cmd = "ip link set " + dev_ + " type can bitrate " + std::to_string(baudrate);
    std::string startup_cmd       = "ip link set " + dev_ + " up";

    (void) system(shut_down_cmd.c_str());
    (void) system(set_baud_rate_cmd.c_str());
    (void) system(startup_cmd.c_str());
}
