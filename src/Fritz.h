//
// Created by Shikang on 2018/1/20.
//

#ifndef FRITZ_CONTROL_FRITZ_H
#define FRITZ_CONTROL_FRITZ_H

#include "Robot.h"
#include "WorkMgr.h"
#include <thread>
#include <mutex>
#include <thread>

class Fritz {
private:
    Serial* serial_ptr;
    Robot* FRobot_ptr;
    WorkMgr workMgr;
    FritzState FState;
    std::mutex SMutex;
    std::thread ControlThread;
public:
    Fritz();
    Fritz(std::string PortName);
    ~Fritz();
    void InitFritz();
    void Idle();
    void Work();
    void Terminate();

};


#endif //FRITZ_CONTROL_FRITZ_H
