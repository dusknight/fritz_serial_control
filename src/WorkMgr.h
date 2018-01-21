//
// Created by Shikang on 2018/1/20.
//

#ifndef FRITZ_CONTROL_WORKMGR_H
#define FRITZ_CONTROL_WORKMGR_H
#include "Robot.h"
#include <thread>
#include <mutex>
#include <thread>

typedef enum {
    Idle = 0,
    Working = 1,
    Close = 2
} FritzState;

class WorkMgr {
private:
    Serial* serial_ptr;
    Robot* FRobot_ptr;
    int work_stage = 0;

    FritzState FState;
    std::mutex SMutex;
    std::thread ControlThread;
public:
    WorkMgr();
    WorkMgr(std::string PortName);
    ~WorkMgr();
    void InitFritz();

    void IdleAnimate();
    void WorkAnimate(int words, int timeMilliSec);
    void TerminateAnimate();

    void DoAnimate();
};


#endif //FRITZ_CONTROL_WORKMGR_H
