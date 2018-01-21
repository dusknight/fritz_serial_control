//
// Created by Shikang on 2018/1/20.
//
#ifdef __CYGWIN__
#define PORT "/dev/ttyS3"
#define VIRTUAL_PORT "/dev/ttyS4"
#elif defined(__unix__)
#define PORT "/dev/ttyUSB0"
#endif

#include "WorkMgr.h"

WorkMgr::WorkMgr(){
    serial_ptr = new Serial();
    serial_ptr->arduino_port_name = PORT;
    FRobot_ptr = new Robot(serial_ptr);
    FState = Close;
}

WorkMgr::WorkMgr(std::string PortName){
    serial_ptr = new Serial();
    serial_ptr->arduino_port_name = PortName;
    FRobot_ptr = new Robot(serial_ptr);
    FState = Close;
}

WorkMgr::~FWorkMgrritz(){
    delete FRobot_ptr;
    delete serial_ptr;
}

void WorkMgr::InitFritz() {

}

//void Fritz::Idle(){
//    SMutex.lock();
//    FState = Idle;
//    SMutex.unlock();
//    Idle
//}
void WorkMgr::IdleAnimate(){

}

void WorkMgr::TerminateAnimate() {

}

void WorkMgr::WorkAnimate(int words, int timeMilliSec) {
    double timePerWord = timeMilliSec / words;

}

void WorkMgr::DoAnimate(){

}