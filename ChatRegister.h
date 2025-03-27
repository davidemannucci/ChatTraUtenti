#include <iostream>
#include <map>
#include "Chat.h"

class ChatRegister{
    private:
        std::map<std::pair<int, int>, Chat> chats;
    public:
        void printRegister() const;
        void addChat(const Chat& chat);
        void deleteChat(int id1, int id2);
        Chat& findChat(int id1, int id2);
};