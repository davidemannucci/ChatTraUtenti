#include <iostream>
#include <map>
#include "Chat.h"

class ChatRegister{
public:
    std::map<std::pair<int, int>, Chat> chats;
    void printRegister() const;
    void addChat(const Chat& chat);
    void deleteChat(int id1, int id2);
    Chat& findChat(int id1, int id2);
};