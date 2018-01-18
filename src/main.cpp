#include <iostream>
#include "Serial.h"

#ifdef __CYGWIN__
#define PORT "/dev/ttyS3"
#elif defined(__unix__)
#define PORT "/dev/ttyUSB0"
#endif

int main() {
    std::cout << "Hello, World!" << std::endl;
    Serial serial_test;
    serial_test.arduino_port_name = PORT;
    serial_test.Open();
    int version = serial_test.TestSerial();  // todo: test fail
    std::cout<<"version="<<version<<std::endl;
//    system("pause");
    return 0;
}