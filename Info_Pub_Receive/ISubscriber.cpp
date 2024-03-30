//
// Created by Q on 2024/3/15.
//
#include "ISubscriber.h"

void ISubscriber::receive(const std::string& _message) {
    std::lock_guard<std::mutex> lock(mutex_);
    message=_message;
}

std::string ISubscriber::GetMessage() {
    std::lock_guard<std::mutex> lock(mutex_);
    return message;
}

std::string ISubscriber::GetSubName() {
    return topic;
}
