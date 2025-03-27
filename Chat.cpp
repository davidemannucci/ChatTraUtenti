#include "Chat.h"
#include "User.h"
#include "Message.h"

void Chat::sendMessage(const Message& message) {
    chatMessages.push_back(message);
}

void Chat::showChat(){
    std::cout << "Chat tra " << user1.getName() << " e " << user2.getName() << ":\n";
    for (const auto& message : chatMessages) {
        message.printMessage();
    }
    std::cout << "-----------------------\n"<<std::endl;
}

void Chat::printChatInfo() const {
    std::cout<<"Chat tra "<< user1.getName()  <<" (ID: "<<user1.getId()<<") e "<<user2.getName() <<" (ID: "<<user2.getId()<<")"<<std::endl;
}

void Chat::deleteMessage(int index) {
    if (index < 0 || index >= chatMessages.size()) {
        throw std::out_of_range("Errore: indice messaggio non valido!");
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
