//
// Created by Q on 2024/3/15.
//

#ifndef MACHINE_GUI_ISUBSCRIBER_H
#define MACHINE_GUI_ISUBSCRIBER_H

#include "iostream"
#include "mutex"

class ISubscriber{
public:
    explicit ISubscriber(const std::string &_topic){
        topic=_topic;
    }
    void receive(const std::string& _message );
    std::string GetSubName();
    std::string GetMessage();
private:
    std::string message;
    std::string topic;
    std::mutex mutex_;

};

#include "ISubscriber.cpp"
#endif //MACHINE_GUI_ISUBSCRIBER_H
