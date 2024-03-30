//
// Created by Q on 2024/3/15.
//

#ifndef MACHINE_GUI_MESSAGECENTER_H
#define MACHINE_GUI_MESSAGECENTER_H
#include "iostream"
#include "unordered_map"
#include "ISubscriber.h"
#include "IPublisher.h"
#include "vector"
#include "memory"
#include <mutex>
#include <atomic>
#include <thread>
// 消息中心，负责管理订阅关系和消息分发

class MessageCenter {
public:
    // 提供一个全局访问点
    static MessageCenter& getInstance();
    void Subscribe(std::shared_ptr<IPublisher> iPublisher, const std::shared_ptr<ISubscriber>& subscriber);
    void UnSubscribe(const std::shared_ptr<IPublisher>& iPublisher, const std::shared_ptr<ISubscriber>& subscriber);
    void AddPublisher(const std::shared_ptr<IPublisher>& iPublisher);
    void DelPublisher(const std::shared_ptr<IPublisher>& iPublisher);
    void publish();
    void publish(const std::shared_ptr<IPublisher>&);
    void GetSubInfo();
    void Start();
    void Stop();
    void Run();



private:
    MessageCenter()=default;
    // 删除拷贝构造函数和拷贝赋值运算符，确保单例
    MessageCenter(const MessageCenter&) = delete;
    MessageCenter& operator=(const MessageCenter&) = delete;

private:
    //私有成员
    std::unordered_map<std::shared_ptr<IPublisher> ,std::vector<std::shared_ptr<ISubscriber>>> subscribers;
    std::mutex mutex_; // 用于线程安全
    std::atomic<bool> publishing_flag;
    double publish_frequency=50;
};


#include "MessageCenter.cpp"
#endif //MACHINE_GUI_MESSAGECENTER_H
