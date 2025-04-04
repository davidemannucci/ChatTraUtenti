#include "Chat.h"
#include "User.h"
#include "Message.h"
#include <sstream>

void Chat::sendMessage(const Message& message) {
    const User& messageSender = message.getSender();
    const User& messageAddressee = message.getAddressee();

    bool isValid = (messageSender.getId() == user1.getId() && messageAddressee.getId() == user2.getId()) ||
                   (messageSender.getId() == user2.getId() && messageAddressee.getId() == user1.getId());
    if (!isValid) {
        throw std::invalid_argument("Il messaggio non appartiene a questa chat.");
    }
    chatMessages.push_back(message);
}

std::string Chat::toStringChat() const {
    std::stringstream ss;
    ss << "Nome chat: " << name << "\n";
    for (const auto& message : chatMessages) {
        ss << message.toStringMessage();
    }
    ss << "-----------------------\n";
    return ss.str();
}

void Chat::deleteMessage(int index) {
    if (index < 0 || index >= chatMessages.size()) {
        throw std::out_of_range("Indice messaggio non valido!");
    }
    chatMessages.erase(chatMessages.begin() + index);
}

const Message& Chat::getMessage(int index) const {
    if (index < 0 || index >= chatMessages.size()) {
        throw std::out_of_range("Indice messaggio non valido!");
    }
    return chatMessages[index];
}

int Chat::getUser1Id() const {
    return user1.getId();
}

int Chat::getUser2Id() const {
    return user2.getId();
}

void Chat::markMessageAsRead(int index) {
    if (index < 0 || index >= chatMessages.size()) {
        throw std::out_of_range("Indice messaggio non valido!");
    }
    chatMessages[index].markAsRead();
}

int Chat::getUnreadMessageCount() const {
    int count = 0;
    for (const auto& message : chatMessages) {
        if (!message.isRead()) {
            count++;
        }
    }
    return count;
}

int Chat::getTotalMessages() const {
    return chatMessages.size();
}

const std::string& Chat::getChatName() const{
    return name;
}

