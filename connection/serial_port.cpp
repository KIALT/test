#include "serial_port.h"
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

SerialPort::SerialPort(const Options &options) : options_(options) {}

SerialPort::~SerialPort() { Close(); }

int SerialPort::Open() {
    fd_ = ::open(options_.port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_ == -1) {
        return kOpenError;
    }

    if (tcgetattr(fd_, &tio_) != 0) {
        return kConfigError;
    }

    tio_.c_cflag |= CLOCAL | CREAD;
    tio_.c_cflag &= ~CSIZE;

    switch (options_.parity) {
    case 'n':
    case 'N':
        tio_.c_cflag |= PARENB;
        break;
    case 'o':
    case 'O':
        tio_.c_cflag |= PARENB | PARODD;
        break;
    case 'e':
    case 'E':
        tio_.c_cflag |= PARENB;
        tio_.c_cflag &= ~PARODD;
        break;
    default:
        tio_.c_cflag |= PARENB;
        break;
    }

    switch (options_.dataBits) {
    case kData5:
        tio_.c_cflag |= CS5;
        break;
    case kData6:
        tio_.c_cflag |= CS6;
        break;
    case kData7:
        tio_.c_cflag |= CS7;
        break;
    case kData8:
        tio_.c_cflag |= CS8;
        break;
    default:
        tio_.c_cflag |= CS8;
        break;
    }

    switch (options_.stopBits) {
    case kOneStop:
        tio_.c_cflag |= CSTOPB;
        break;
    case kOneAndHalfStop:
        tio_.c_cflag |= CSTOPB;
        break;
    default:
        tio_.c_cflag |= CSTOPB;
        break;
    }

    switch (options_.baudRate) {
    case 2400:
        cfsetispeed(&tio_, B2400);
        cfsetospeed(&tio_, B2400);
        break;
    case 4800:
        cfsetispeed(&tio_, B4800);
        cfsetospeed(&tio_, B4800);
        break;
    case 9600:
        cfsetispeed(&tio_, B9600);
        cfsetospeed(&tio_, B9600);
        break;
    case 19200:
        cfsetispeed(&tio_, B19200);
        cfsetospeed(&tio_, B19200);
        break;
    case 38400:
        cfsetispeed(&tio_, B38400);
        cfsetospeed(&tio_, B38400);
        break;
    case 57600:
        cfsetispeed(&tio_, B57600);
        cfsetospeed(&tio_, B57600);
        break;
    case 115200:
        cfsetispeed(&tio_, B115200);
        cfsetospeed(&tio_, B115200);
        break;
    case 230400:
        cfsetispeed(&tio_, B230400);
        cfsetospeed(&tio_, B230400);
        break;
    default:
        cfsetispeed(&tio_, B9600);
        cfsetospeed(&tio_, B9600);
        break;
    }

    switch (options_.flowControl) {
    case kNoFlowControl:
        tio_.c_cflag &= ~CRTSCTS;
        break;
    case kHardwareFlowControl:
        tio_.c_cflag |= CRTSCTS;
        break;
    }

    tio_.c_cc[VTIME] = 0;
    tio_.c_cc[VMIN]  = 0;

    tcflush(fd_, TCIFLUSH);
    if (tcsetattr(fd_, TCSANOW, &tio_) != 0) {
        return kConfigError;
    }

    return kNoError;
}

void SerialPort::Close() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool SerialPort::IsOpen() const { return fd_ != -1; }

int SerialPort::Flush() { return tcflush(fd_, TCIFLUSH); }

int SerialPort::Read(uint8_t *buf, size_t len) { return ::read(fd_, buf, len); }

int SerialPort::Write(const uint8_t *buf, size_t len) { return ::write(fd_, buf, len); }
