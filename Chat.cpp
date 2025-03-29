#include "Chat.h"
#include "User.h"
#include "Message.h"

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

void Chat::showChat(){
    std::cout << "Chat tra " << user1.getName() << " e " << user2.getName() << ":\n";
    for (const auto& message : chatMessages) {
        message.printMessage();
    }
    std::cout << "-----------------------\n"<<std::endl;
}

void Chat::deleteMessage(int index) {
    if (index < 0 || index >= chatMessages.size()) {
        throw std::out_of_range("Indice messaggio non valido!");
    }
    std::cout << "\nEliminando messaggio: ";
    chatMessages[index].printMessage();
    chatMessages.erase(chatMessages.begin() + index);

    std::cout << "Messaggio eliminato con successo!\n";
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
        if (!message.IsRead()) {
            count++;
        }
    }
    return count;
}

int Chat::getTotalMessages() const {
    return chatMessages.size();
}

const std::string Chat::getChatName() const{
    return name;
}

