#include "Serial.h"
#include "Robot.h"
#include "Animate.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef __CYGWIN__
#define PORT "/dev/ttyS3"
#define VIRTUAL_PORT "/dev/ttyS4"
#elif defined(__unix__)
#define PORT "/dev/ttyUSB0"
#endif

int testSerial(){
    Serial serial_test;
    serial_test.arduino_port_name = PORT;
    serial_test.Open();
    int version = serial_test.TestSerialOld();
    std::cout<<"version="<<version<<std::endl;
    serial_test.Close();
}

int testRobot(){
    auto serial_test_ptr = new Serial();
    serial_test_ptr->arduino_port_name = PORT;
    Robot robot_test(serial_test_ptr);
    robot_test.InitRobot();
    robot_test.SetCentre();
    std::cout<<"Center Set"<<std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    robot_test.SetLeft();
    std::cout<<"Left Set"<<std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    robot_test.SetRight();
    std::cout<<"Right Set"<<std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    robot_test.SetCentre();
    std::cout<<"Center Set"<<std::endl;
    serial_test_ptr->Close();
    return 0;
}

int testAnimate(){
    auto serial_test_ptr = new Serial();
    serial_test_ptr->arduino_port_name = PORT;
    Animate animate(serial_test_ptr);
    animate.Init();
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    animate.Abort();
}

int testSpeak(){
    auto serial_test_ptr = new Serial();
    serial_test_ptr->arduino_port_name = PORT;
    Animate animate(serial_test_ptr);
    animate.Init();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    auto SpeakSeries = GetSpeakSeries();
    auto NodSeries = GetNodSeries();
    animate.q_state_series.push(SpeakSeries);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    animate.ClearWork();
    animate.q_state_series.push(NodSeries);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    animate.ClearWork();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    animate.Abort();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
//    testSerial();
//    testRobot();
//    testAnimate();
    testSpeak();
//    system("pause");
    return 0;
}