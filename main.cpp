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
    Chat chat1(Francesco, Marco);
    Chat chat2(Marco, Maria);
    Message message1("Ciao", Francesco, Marco);
    Message message2("Ciao Francesco", Marco, Francesco);
    Message message3("Come va?", Francesco, Marco);
    Message message4("Tutto bene", Marco, Francesco);
    Message message5("Buongiorno Marco!", Maria, Marco);
    std::cout << "Francesco ID: " << idFrancesco << std::endl;
    std::cout << "Marco ID: " << idMarco << std::endl;
    std::cout<<"Maria ID: "<< idMaria<< std::endl;

    message1.markAsRead();
    chat1.sendMessage(message1);

    message2.markAsRead();
    chat1.sendMessage(message2);

    message3.markAsRead();
    chat1.sendMessage(message3);

    chat1.sendMessage(message4);

    chat1.showChat();

    chat2.sendMessage(message5);
    chat2.showChat();

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
        foundChat.showChat();
    } catch (const std::runtime_error& e) {
        std::cout << "Errore: "<< e.what()<<std::endl;
    }

    try {
        std::cout << "\nCercando nel registro la chat tra Marco e Francesco...\n";
        Chat& foundChat = registerChat.findChat(idMarco, idFrancesco);
        foundChat.showChat();
    } catch (const std::runtime_error& e) {
        std::cout << "Errore: "<< e.what()<<std::endl;
    }

    try {
        chat1.deleteMessage(1);  // Elimina il secondo messaggio
        chat1.showChat();
    } catch (const std::out_of_range& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }


    return 0;
}
