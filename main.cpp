#include <iostream>
#include <ctime>
#include "ChatRegister.h"
#include "User.h"
#include "Chat.h"
#include "Message.h"

int main() {
    srand(time(0));
    ChatRegister registerChat;
    User Francesco("Francesco");
    int idFrancesco = Francesco.getId();
    User Maria("Maria");
    int idMaria = Maria.getId();
    User Marco("Marco");
    int idMarco = Marco.getId();
    Chat chat1("Chat tra Francesco e Marco",Francesco, Marco);
    Chat chat2("Chat tra Marco e Maria",Marco, Maria);
    Message message1("Ciao", Francesco, Marco);
    Message message2("Ciao Francesco", Marco, Francesco);
    Message message3("Come va?", Francesco, Marco);
    Message message4("Tutto bene", Marco, Francesco);
    Message message5("Buongiorno Marco!", Maria, Marco);
    std::cout << Francesco.toStringUser() << std::endl;
    std::cout << Marco.toStringUser() << std::endl;
    std::cout << Maria.toStringUser() << "\n" << std::endl;


    chat1.sendMessage(message1);

    chat1.markMessageAsRead(0);

    chat1.sendMessage(message2);

    chat1.sendMessage(message3);

    chat1.sendMessage(message4);

    std::string Chat1= chat1.toStringChat();
    std::cout<<Chat1<<std::endl;

    int unreadMessages= chat1.getUnreadMessageCount();
    int totalMessages = chat1.getTotalMessages();

    std::cout<< "Messaggi totali della "<<chat1.getChatName()<<": "<<totalMessages<<std::endl;
    std::cout<< "Messaggi non letti della "<<chat1.getChatName()<<": "<<unreadMessages<<"\n"<<std::endl;

    chat2.sendMessage(message5);
    std::string Chat2= chat2.toStringChat();
    std::cout<<Chat2<<std::endl;

    try {
        std::cout << "\nAggiungendo al registro la chat tra Francesco e Marco...\n";
        registerChat.addChat(chat1);
    } catch (const std::exception& e) {
        std::cout<< e.what() <<std::endl;
    }

    try {
        std::cout << "\nAggiungendo al registro la chat tra Marco e Maria...\n";
        registerChat.addChat(chat2);
    } catch (const std::exception& e) {
        std::cout<< e.what() << std::endl;
    }

    registerChat.printRegister();

    try {
        std::cout << "\nEliminando dal registro la chat tra Francesco e Maria...\n";
        registerChat.deleteChat(idFrancesco, idMaria);
    } catch (const std::runtime_error& e) {
        std::cout<< "Errore: " << e.what() <<std::endl;
    }

    try {
        std::cout << "\nEliminando dal registro la chat tra Maria e Marco...\n";
        registerChat.deleteChat(idMaria, idMarco);
    } catch (const std::runtime_error& e) {
        std::cout<< "Errore: " << e.what() <<std::endl;
    }

    try {
        std::cout << "\nAggiungendo al registro la chat tra Francesco e Marco...\n";
        registerChat.addChat(chat1);
    } catch (const std::exception& e) {
        std::cout<< e.what() <<std::endl;
    }

    registerChat.printRegister();

    try {
        std::cout << "\nCercando nel registro la chat tra Maria e Francesco...\n";
        Chat& foundChat = registerChat.findChat(idMaria, idMarco);
        foundChat.toStringChat();
    } catch (const std::runtime_error& e) {
        std::cout << "Errore: "<< e.what()<<std::endl;
    }

    try {
        std::cout << "\nCercando nel registro la chat tra Marco e Francesco...\n";
        Chat& foundChat = registerChat.findChat(idMarco, idFrancesco);
        std::cout<< foundChat.toStringChat();
    } catch (const std::runtime_error& e) {
        std::cout << "Errore: "<< e.what()<<std::endl;
    }

    try {
        std::cout << "\nRecupero del primo messaggio nella chat tra Francesco e Marco:\n";
        const Message& firstMessage = chat1.getMessage(0);
        std::cout << "Contenuto: " << firstMessage.toStringMessage()<<std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    try {
        chat1.deleteMessage(1);  // Elimina il secondo messaggio
        std::cout<< chat1.toStringChat();
    } catch (const std::out_of_range& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }


    return 0;
}
