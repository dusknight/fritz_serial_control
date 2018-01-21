//
// Created by Shikang on 2018/1/20.
//
#ifdef __CYGWIN__
#define PORT "/dev/ttyS3"
#define VIRTUAL_PORT "/dev/ttyS4"
#elif defined(__unix__)
#define PORT "/dev/ttyUSB0"
#endif

#include "Fritz.h"

Fritz::Fritz(){
    serial_ptr = new Serial();
    serial_ptr->arduino_port_name = PORT;
    FRobot_ptr = new Robot(serial_ptr);
    FState = Close;
}

Fritz::Fritz(std::string PortName){
    serial_ptr = new Serial();
    serial_ptr->arduino_port_name = PortName;
    FRobot_ptr = new Robot(serial_ptr);
    FState = Close;
}

Fritz::~Fritz(){
    delete FRobot_ptr;
    delete serial_ptr;
}

void Fritz::InitFritz() {

}

//void Fritz::Idle(){
//    SMutex.lock();
//    FState = Idle;
//    SMutex.unlock();
//    Idle
//}
void Fritz::IdleAnimate(){

}

void Fritz::TerminateAnimate() {

}

void Fritz::WorkAnimate(int words, int timeMilliSec) {
    double timePerWord = timeMilliSec / words;

}