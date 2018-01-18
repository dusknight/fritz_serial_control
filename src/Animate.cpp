//
// Created by Shikang on 2018/1/18.
//

#include "Animate.h"
#include <chrono>
#include <thread>
#include <iostream>

Animate::Animate(Serial *serial)
{
    _working = false;
    _abort = false;
    _serial = serial;

//    text << "Good morning! How are you?"
//         << "My brain is a Raspberry Pi"
//         << "My muscles are an Arduino Microcontroller"
//         << "It is a nice day!"
//         << "Did you have your coffee yet?"
//         << "My name is Fritz!"
//         << "I am a robot! Are you a robot?"
//         << "I was programmed by Phil"
//         << "I have 13 movable parts"
//         << "I am nearly 2 years old";
    text = "Good morning! How are you?";
}

void Animate::doWork()
{
    int dir = 1;
    int angle = 10;

    _working = false;
    _abort = false;

    double sonar = 0;
    double previous = 9999;
    bool running = true;
    Robot robot(_serial);

    robot.SetCentre();
//    I::msleep(500);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    while(running)
    {
        mutex.lock();
        sonar = robot.GetSonar();
        //qWarning() << "Sonar: " << sonar << endl;
        running = !_abort;
        mutex.unlock();
//        I::msleep(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if(sonar <= 50 && sonar != previous)
        {
            mutex.lock();
            robot.SetExpression();
//            I::msleep(1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if(previous > 50)
            {
                SpeakMessage("Hello my name is Fritz");
            }
            else
            {
                std::string command = "fortune cookies.txt";
                QProcess process;
                process.start(command);
                process.waitForFinished();
                std::string output(process.readAllStandardOutput());
                SpeakMessage(output);
//                qWarning() << output;
                std::clog<<output;
            }
            previous = sonar;
            sonar = 9999;
            mutex.unlock();
//            I::msleep(2000);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if(sonar > 50)
        {
            angle = angle + (5 * dir);
            if( angle >= 90 || angle <= 10 )
            {
                dir = dir * -1;
            }
            //qWarning() << QObject::tr("Angle %1").arg(angle) << endl;
            robot.SetNeck(angle);
            //I::msleep(100);
        }
    }
    emit done();
    emit finished();
}

void Animate::doWorkOld()
{
    Robot robot(_serial);
    QTime time = QTime::currentTime();
    srand((uint)time.msec());

    int dir = 1;
    int angle = 10;
    double previous = 9999;
    robot.SetCentre();
    robot.SetNeck(angle);

    bool running = true;
    while(running)
    {
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();
        if (abort)
        {
            running = false;
            break;
        }

        int value = (int)(qrand() % 10);
        mutex.lock();
        double sonar = robot.GetSonar();
        //qWarning() << "Sonar: " << sonar << endl;
        mutex.unlock();

        //if( sonar < 9999)
        //{
        //qWarning() << QObject::tr("SonarValue %1").arg(sonar) << endl;
        if(sonar <= 40.0 && sonar != previous)
        {
            QString msg = text.at(value);
            SpeakMessage(msg);
            I::sleep(10);
            previous = sonar;
        }
        if(sonar > 40)
        {
            angle = angle + (5 * dir);
            if( angle >= 90 || angle <= 10 )
            {
                dir = dir * -1;
            }
            //qWarning() << QObject::tr("Angle %1").arg(angle) << endl;
            robot.SetNeck(angle);
            I::msleep(500);
            //}
        }
    }
    emit done();
    emit finished();
}

void Animate::SpeakMessage(std::string msg)
{
    //Speak speak;
    Robot robot(_serial);

    robot.SpeakMessage(msg);
    return;

//    QStringList phons = speak.TextToPhon(msg);
//    speak.TextToSpeech(msg);

//    QStringListIterator iterator(phons);
//    while (iterator.hasNext())
//    {
//        QString shape = speak.GetMouthShape(iterator.next());
//        robot.SetMouth(shape);
//        I::msleep(10);
//    }
}

void Animate::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    mutex.unlock();

    emit workRequested();
}

void Animate::abort()
{
    //if (_working) {
    mutex.lock();
    _working = false;
    _abort = true;
    mutex.unlock();
    //}
}
