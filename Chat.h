#include <iostream>
#include "User.h"
#include "Message.h"
#include <vector>
#ifndef CHAT_H
#define CHAT_H

class Chat{
    public:
        Chat(const std::string& name, const User& user1, const User& user2) : name(name), user1(user1), user2(user2){}

        void sendMessage(const Message& message);
        std::string toStringChat() const;
        void deleteMessage(int index);
        const Message& getMessage(int index) const;
        int getUser1Id() const;
        int getUser2Id() const;
        int getUnreadMessageCount() const;
        int getTotalMessages() const;
        void markMessageAsRead(int index);
        const std::string& getChatName() const;

    private:
        std::string name;
        User user1, user2;
        std::vector<Message> chatMessages;
};

#endif
