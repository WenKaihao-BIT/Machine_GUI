//
// Created by Q on 2024/3/15.
//

#ifndef MACHINE_GUI_IPUBLISHER_H
#define MACHINE_GUI_IPUBLISHER_H
#include "mutex"
#include "memory"
class IPublisher{

public:
//    explicit IPublisher(const std::string& _topic):topic(_topic){}
    virtual ~IPublisher(){}
    explicit IPublisher(const std::string&_topic):topic(_topic){}
    std::string GetMessage();
    void UpdateMessage(const std::string& new_message);
    std::string GetTopic();

private:
    std::string message;
    std::mutex mutex_;
    std::string topic;


};

#include "IPublisher.cpp"
#endif //MACHINE_GUI_IPUBLISHER_H
