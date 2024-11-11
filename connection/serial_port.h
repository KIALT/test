#pragma once

#include <string>
#include <termios.h>

class SerialPort
{
public:
    struct Options {
        std::string port;        /* 串口名称*/
        int         baudRate;    /* 波特率*/
        int         dataBits;    /* 数据位*/
        int         stopBits;    /* 停止位*/
        int         parity;      /* 校验位*/
        int         flowControl; /* 流控制*/
    };

    enum ParityEnum {
        kNoParity    = 'N', /* 无校验   */
        kEvenParity  = 'O', /* 奇校验   */
        kOddParity   = 'E', /* 偶校验   */
        kSpaceParity = 'S', /* 空格校验 */
        kMarkParity  = 'M', /* 标记校验 */
    };

    enum DataBitsEnum {
        kData5 = 5, /* 5位数据位 */
        kData6 = 6, /* 6位数据位 */
        kData7 = 7, /* 7位数据位 */
        kData8 = 8, /* 8位数据位 */
    };

    enum StopBitsEnum {
        kOneStop         = 1, /* 1位停止位 */
        kOneAndHalfStop  = 2, /* 1.5位停止位 */
        kTwoStop         = 3, /* 2位停止位 */
        kUnknownStopBits = -1 /* 未知停止位 */
    };

    enum FlowControlEnum {
        kNoFlowControl       = 0, /* 无流控制 */
        kHardwareFlowControl = 1, /* 硬件流控制 */
        kSoftwareFlowControl = 2, /* 软件流控制 */
        kUnknownFlowControl  = -1 /* 未知流控制 */
    };

    enum ErrorEnum {
        kNoError = 0,       /* 无错误 */
        kOpenError = -1,     /* 打开串口失败 */
        kConfigError = -2,   /* 配置串口失败 */
        kInvalidParam = -3,   /* 无效参数 */
    };

public:
    SerialPort(const Options &options);
    ~SerialPort();

    int  Open();
    void Close();
    bool IsOpen() const;
    int  Flush();
    int  Read(uint8_t *buf, size_t len);
    int  Write(const uint8_t *buf, size_t len);

private:
    int            fd_;
    Options        options_;
    struct termios tio_;
};
