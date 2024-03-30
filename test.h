//
// Created by Q on 2024/3/15.
//

#ifndef MACHINE_GUI_TEST_H
#define MACHINE_GUI_TEST_H
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <mutex>

class ISubscriber {
public:
    virtual ~ISubscriber() = default;
    virtual void receive(const std::string& message) = 0;
};

class MessageCenter {
public:
    // 删除拷贝构造函数和拷贝赋值运算符，确保单例
    MessageCenter(const MessageCenter&) = delete;
    MessageCenter& operator=(const MessageCenter&) = delete;

    // 提供一个全局访问点
    static MessageCenter& getInstance() {
        static MessageCenter instance;
        return instance;
    }

    void subscribe(const std::string& topic, std::shared_ptr<ISubscriber> subscriber) {
        std::lock_guard<std::mutex> lock(mutex_);
        subscribers[topic].push_back(subscriber);
    }

    void publish(const std::string& topic, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (subscribers.find(topic) != subscribers.end()) {
            for (auto& subscriber : subscribers[topic]) {
                subscriber->receive(message);
            }
        }
    }

private:
    // 私有构造函数
    MessageCenter() = default;

    std::map<std::string, std::vector<std::shared_ptr<ISubscriber>>> subscribers;
    std::mutex mutex_; // 用于线程安全
};

#endif //MACHINE_GUI_TEST_H
