//
// Created by Q on 2024/3/15.
//
#include "IPublisher.h"


std::string IPublisher::GetMessage() {
    return message;
}

void IPublisher ::UpdateMessage(const std::string& new_message) {
    std::lock_guard<std::mutex> lock(mutex_);
    message=new_message;
}

std::string IPublisher::GetTopic() {
    return topic;
}
