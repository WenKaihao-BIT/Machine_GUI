//
// Created by Q on 2024/3/15.
//
#include "MessageCenter.h"
#include "algorithm"

MessageCenter &MessageCenter::getInstance() {
    static MessageCenter instance;
    return instance;
}


void MessageCenter::AddPublisher(const std::shared_ptr<IPublisher>& iPublisher) {
    if(subscribers.find(iPublisher)==subscribers.end())
        subscribers[iPublisher]=std::vector<std::shared_ptr<ISubscriber>>();
}

void MessageCenter::DelPublisher(const std::shared_ptr<IPublisher>& iPublisher) {
    if(subscribers.find(iPublisher)!=subscribers.end())
        subscribers.erase(iPublisher);
}
void MessageCenter::Subscribe(std::shared_ptr<IPublisher>iPublisher, const std::shared_ptr<ISubscriber>& subscriber) {
    //添加订阅topic
    std::lock_guard<std::mutex> lock(mutex_);
    if(std::find(subscribers[iPublisher].begin(),subscribers[iPublisher].end(),subscriber)==subscribers[iPublisher].end())
        subscribers[iPublisher].push_back(subscriber);
}



void MessageCenter::publish(const std::shared_ptr<IPublisher>& iPublisher) {
    /*转发订阅指定topic的信息*/
    std::lock_guard<std::mutex>lock(mutex_);
    if (subscribers.find(iPublisher) != subscribers.end()) {
        std::string _message=iPublisher->GetMessage();
        for (auto& subscriber : subscribers[iPublisher]) {
            subscriber->receive(_message);
        }
    }
}
void MessageCenter::publish() {
    /*向对应的topic转发话题*/
    std::lock_guard<std::mutex>lock(mutex_);
    for(const auto& topic_pair:subscribers){
        //拿到每个topic 的信息
        std::string message=topic_pair.first->GetMessage();
        for(const auto& subscriber:topic_pair.second)
            subscriber->receive(message);
    }
}
void MessageCenter::Stop() {
        if(publishing_flag){
            publishing_flag= false;
            std::cout<<"---MessageCenter Stop---"<<std::endl;
        }
}

void MessageCenter::Start() {
        if(!publishing_flag){
            publishing_flag= true;
            Run();
        }
}

void MessageCenter::Run() {
    while (publishing_flag){
        std::this_thread::sleep_for(std::chrono::seconds(int(1/publish_frequency)));
        publish();
    }
}

void MessageCenter::GetSubInfo() {
    std::cout<<"---------------------"<<std::endl;
    for(auto topic_pair:subscribers){
        std::cout<<(topic_pair.first)->GetTopic()<<"---";
       for(auto subscriber:topic_pair.second){
           std::cout<<subscriber->GetSubName()<<' ';
       }
       std::cout<<std::endl;
    }
    std::cout<<"---------------------"<<std::endl;
}

void MessageCenter::UnSubscribe(const std::shared_ptr<IPublisher>& iPublisher, const std::shared_ptr<ISubscriber>& subscriber) {
    //函数功能：取消subscriber对publisher的订阅
    std::lock_guard<std::mutex> lock(mutex_);
    auto cur=std::find(subscribers[iPublisher].begin(),subscribers[iPublisher].end(),subscriber);
    if(cur!=subscribers[iPublisher].end())
        subscribers[iPublisher].erase(cur);
}

