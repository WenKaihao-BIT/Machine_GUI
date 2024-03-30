#include <iostream>

#include "Info_Pub_Receive/IPublisher.h"
#include "Info_Pub_Receive/MessageCenter.h"
#include "memory"
using namespace std;
int main() {
    shared_ptr<IPublisher>ptr1= make_shared<IPublisher>("motor1");
    shared_ptr<IPublisher>ptr2= make_shared<IPublisher>("motor2");
    shared_ptr<IPublisher>ptr3= make_shared<IPublisher>("Camera");
    MessageCenter& messageCenter=MessageCenter::getInstance();
//    messageCenter.GetSubInfo();
    messageCenter.AddPublisher(ptr1);
    messageCenter.AddPublisher(ptr2);
    messageCenter.AddPublisher(ptr3);
//    messageCenter.GetSubInfo();
    messageCenter.DelPublisher(ptr1);
//    messageCenter.GetSubInfo();
    shared_ptr<ISubscriber>sptr1= make_shared<ISubscriber>("plot");
    messageCenter.Subscribe(ptr1,sptr1);
    messageCenter.Subscribe(ptr3,sptr1);
    messageCenter.GetSubInfo();
    messageCenter.UnSubscribe(ptr1,sptr1);
    messageCenter.GetSubInfo();
    messageCenter.Start();
    messageCenter.Run();
//    std::cout<<sptr1->GetSubName()<<std::endl;
//    std::string message="hello world";
//    iPublisher.UpdateMessage(message);
//    std::cout<<iPublisher.GetMessage()<<std::endl;
//    std::cout<<iPublisher.GetTopic()<<std::endl;

    return 0;
}
