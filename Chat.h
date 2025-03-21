#include <iostream>
#include "User.h"
#include "Message.h"
#include <vector>
#ifndef CHAT_H
#define CHAT_H

class Chat{
public:
    Chat(const User& user1, const User& user2) : user1(user1), user2(user2){}
    Chat()=default;

    void sendMessage(const Message& message);
    void showChat();
    void printChatInfo() const;
    void deleteMessage(int index);

    User user1, user2;
    std::vector<Message> chatMessages;
};

#endif
