#include "ChatRegister.h"
#include "Chat.h"
#include <map>
#include <vector>

void ChatRegister::addChat(const Chat &chat) {
    std::vector <std::pair<time_t, Chat>> sortedChats;
    int id1 = std::min(chat.user1.id, chat.user2.id);
    int id2 = std::max(chat.user1.id, chat.user2.id);
    if (chats.find({id1, id2}) != chats.end()){
        throw std::runtime_error("Errore: chat gia' esistente!");
    }
    chats[{id1, id2}] = chat;
}

Chat& ChatRegister::findChat(int id1, int id2) {
    int minId = std::min(id1, id2);
    int maxId = std::max(id1, id2);
    auto it = chats.find({minId, maxId});
    if (it == chats.end()) {
        throw std::runtime_error("Chat non trovata!");
    }
    return it->second;
}

void ChatRegister::deleteChat(int id1, int id2) {
    int minId = std::min(id1, id2);
    int maxId = std::max(id1, id2);
    if (chats.erase({minId, maxId})) {
    } else {
        throw std::runtime_error("Chat non trovata!");
    }
}

void ChatRegister:: printRegister() const {
    if (chats.empty()) {
        std::cout << "Il registro è vuoto!" << std::endl;
    } else {
        std::cout << "\nChat nel registro:\n";
        for (const auto& chatPair : chats) {
            const auto& chat = chatPair.second;
            chat.printChatInfo();
        }
    }
}