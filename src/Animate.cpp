//
// Created by Shikang on 2018/1/18.
//

#include "Animate.h"
#include <iostream>

Animate::Animate(Robot* r){
    p_serial = nullptr;
    p_robot = r;
    abort = false;
    work = false;
    q_robot_state = std::queue<RobotState>();
    p_state_mtx = new std::mutex();
}

Animate::Animate(Serial* s) {
    p_serial = s;
    p_robot = new Robot(s);
    abort = false;
    work = false;
    q_robot_state = std::queue<RobotState>();
    p_state_mtx = new std::mutex();
}

Animate::Animate(std::string str) {
    p_serial = new Serial();
    p_serial->arduino_port_name = str;
    p_robot = new Robot(p_serial);
    abort = false;
    work = false;
    q_robot_state = std::queue<RobotState>();
    p_state_mtx = new std::mutex();
}

Animate::Animate(const Animate &a) {
    p_serial = a.p_serial;
    p_robot = a.p_robot;
    abort = a.abort;
    work = a.work;
    p_state_mtx = a.p_state_mtx;
    q_robot_state = a.q_robot_state;
    q_state_series = a.q_state_series;
}

void Animate::Abort(){
    p_state_mtx->lock();
    work = false;
    abort = true;
    q_robot_state = std::queue<RobotState>();
    p_state_mtx->unlock();
}

void Animate::Init(){
    p_state_mtx->lock();
    work = true;
    abort = false;
    p_state_mtx->unlock();
    IdleState = 0;

    p_robot->SetCentre();
    p_work_thread = new std::thread(&StartWork, this);
//    StartWork();
}

void Animate::TransmitState(){
    if(q_state_series.empty()) return;
    StateSeries s = q_state_series.front();
    q_state_series.pop();

    for(auto iter = s.v_robot_state.begin(); iter!=s.v_robot_state.end();iter++){
        q_robot_state.push(*iter);
    }
}

void Animate::StartWork(){
//    Init();
    p_robot->InitRobot();
    DoWork();
}

void Animate::DoWork(){
    while(true){
        p_state_mtx->lock();
        if (not work) return;
        if (abort) return;
        TransmitState();
        if(q_robot_state.empty())
            SetIdle();
        else{
            next_state = q_robot_state.front();
            q_robot_state.pop();
        }
        p_state_mtx->unlock();

        p_robot->SetState(next_state);
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // TODO: check
    }
}

void Animate::SetIdle(){
    IdleState = (IdleState + 1) % 4;
    next_state = IdleStateLst[IdleState];
}

//void Animate::doWork()
//{
//    int dir = 1;
//    int angle = 10;
//
//    _working = false;
//    _abort = false;
//
//    double sonar = 0;
//    double previous = 9999;
//    bool running = true;
//    Robot robot(_serial);
//
//    robot.SetCentre();
////    I::msleep(500);
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//    while(running)
//    {
//        mutex.lock();
//        sonar = robot.GetSonar();
//        //qWarning() << "Sonar: " << sonar << endl;
//        running = !_abort;
//        mutex.unlock();
////        I::msleep(100);
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
//        if(sonar <= 50 && sonar != previous)
//        {
//            mutex.lock();
//            robot.SetExpression();
////            I::msleep(1000);
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//            if(previous > 50)
//            {
//                SpeakMessage("Hello my name is Fritz");
//            }
//            else
//            {
//                std::string command = "fortune cookies.txt";
//                QProcess process;
//                process.start(command);
//                process.waitForFinished();
//                std::string output(process.readAllStandardOutput());
//                SpeakMessage(output);
////                qWarning() << output;
//                std::clog<<output;
//            }
//            previous = sonar;
//            sonar = 9999;
//            mutex.unlock();
////            I::msleep(2000);
//            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//        }
//        if(sonar > 50)
//        {
//            angle = angle + (5 * dir);
//            if( angle >= 90 || angle <= 10 )
//            {
//                dir = dir * -1;
//            }
//            //qWarning() << QObject::tr("Angle %1").arg(angle) << endl;
//            robot.SetNeck(angle);
//            //I::msleep(100);
//        }
//    }
//    emit done();
//    emit finished();
//}

//void Animate::doWorkOld()
//{
//    Robot robot(_serial);
//    QTime time = QTime::currentTime();
//    srand((uint)time.msec());
//
//    int dir = 1;
//    int angle = 10;
//    double previous = 9999;
//    robot.SetCentre();
//    robot.SetNeck(angle);
//
//    bool running = true;
//    while(running)
//    {
//        mutex.lock();
//        bool abort = _abort;
//        mutex.unlock();
//        if (abort)
//        {
//            running = false;
//            break;
//        }
//
//        int value = (int)(qrand() % 10);
//        mutex.lock();
//        double sonar = robot.GetSonar();
//        //qWarning() << "Sonar: " << sonar << endl;
//        mutex.unlock();
//
//        //if( sonar < 9999)
//        //{
//        //qWarning() << QObject::tr("SonarValue %1").arg(sonar) << endl;
//        if(sonar <= 40.0 && sonar != previous)
//        {
//            QString msg = text.at(value);
//            SpeakMessage(msg);
//            I::sleep(10);
//            previous = sonar;
//        }
//        if(sonar > 40)
//        {
//            angle = angle + (5 * dir);
//            if( angle >= 90 || angle <= 10 )
//            {
//                dir = dir * -1;
//            }
//            //qWarning() << QObject::tr("Angle %1").arg(angle) << endl;
//            robot.SetNeck(angle);
//            I::msleep(500);
//            //}
//        }
//    }
//    emit done();
//    emit finished();
//}
