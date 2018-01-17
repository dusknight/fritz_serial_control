//
// Created by Du Shikang on 17/01/2018.
//

#ifndef FRITZ_CONTROL_SERIAL_H
#define FRITZ_CONTROL_SERIAL_H

#include "serial/serial.h"
#include <string>
#include <vector>
#include <cstdint>

//enum class byte : std::uint8_t {};
typedef uint8_t byte;

typedef enum {
    Checked = 0,
    Fail = 1,
} CheckState;

class Serial {
private:
    static const uint32_t BaudRate = 57600;
    static const int ARDUINO_GET_ID = 0; // returns ARDU
    static const int ARDUINO_RESET = 1; //
    static const int ARDUINO_SET_OBJECT = 2; //
    static const int ARDUINO_SET_SERVO = 3; //
    static const int ARDUINO_HEARTBEAT = 4;
    static const int ARDUINO_RELEASE_SERVO = 5;
    static const int ARDUINO_GET_IR = 6;
    static const int ARDUINO_GET_SONAR = 7;

    static const int ARDUINO_LOAD_CONFIG = 32;
    static const int ARDUINO_SAVE_CONFIG = 33;
    static const int ARDUINO_SAVE_SEQUENCE = 34;

    int sendQueueTop;
    int sendQueueBottom;
    bool isRunning;

    int serialPort;

    bool foundBoard;

    double sonarValue;

    int version;

    static const int waitTimeOut = 50;
    static const int readTimeOut = 100;  // TODO: check

    static void convStringVector(const std::string & s, std::vector<byte> & v);
public:

    Serial();
    ~Serial();

    bool IsConnected();

    int Open();

    void Close();

    void DoTest(CheckState state, int min, int max, int pin, int val);

    int TestSerialOld();
//    bool SendPacketOld(std::vector<byte> data, int slen, int rlen);
//    void ReadOld(std::vector<byte> data);
    void Read_(std::vector<byte> buffer, int len);

    int TestSerial();
    bool SendPacket(std::vector<byte> data, int slen, int rlen);
    void handleReadyRead();
    void handleError();

    int GetVersion(std::vector<byte> data);

    int GetVersion();

    double GetSonar();

    void SetSonar(int outPin, int inPin);

    void SetServo(int pin, float value, int max, int min, int trim, bool inverted = false);

    void SetServo(int pin, int value);

    void SendCommand(int cmd);

    void SendCommand(int cmd, int pin);

    void SendCommand(int cmd, int pin, int value);

    void SendCommand(int cmd, int pin, short value);

    void SendCommand(int cmd, int pin, uint8_t value);

    void SendCommand(int cmd, std::vector<int> dat);

    void SendCommand(int cmd, std::vector<byte> dat);

//    QSerialPort *arduino;
    serial::Serial *arduino;
    std::string arduino_port_name;
    bool arduino_is_available;


};


#endif //FRITZ_CONTROL_SERIAL_H
