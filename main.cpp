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
    User Sara("Sara");
    int idSara = Sara.getId();
    Chat chat1(Francesco, Marco);
    Chat chat2(Marco, Maria);
    Chat chat3(Sara, Maria);
    std::cout << "Francesco ID: " << idFrancesco << std::endl;
    std::cout << "Marco ID: " << idMarco << std::endl;
    std::cout<<"Maria ID: "<< idMaria<< std::endl;
    std::cout<<"Sara ID: "<<idSara<<std::endl;

    chat1.sendMessage(Message("Ciao Marco! Come stai?", Francesco, Marco));
    chat1.sendMessage(Message("Ciao Francesco! Sto bene, tu?", Marco, Francesco));
    chat1.sendMessage(Message("Anche io sto bene!", Francesco, Marco));
    chat1.sendMessage(Message("Come va a scuola?", Francesco, Marco));
    chat1.sendMessage(Message("Male, ho troppo da studiare nell'ultimo periodo.", Marco, Francesco));

    chat2.sendMessage(Message("Ciao Marco! Esco ora di casa, ci vediamo tra 30 minuti al parco.", Maria, Marco));
    chat2.sendMessage(Message("Va bene, mi trovi li'.", Marco, Maria));

    chat3.sendMessage(Message("Stasera usciamo?", Sara, Maria));
    chat3.sendMessage(Message("No, oggi non posso.", Maria, Sara));

    chat1.showChat();
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

    try {
        std::cout << "\nAggiungendo al registro la chat tra Sara e Maria...\n";
        registerChat.addChat(chat3);
    } catch (const std::exception& e) {
        std::cout<< e.what() <<std::endl;
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

    registerChat.printRegister();

    try {
        std::cout << "\nCercando nel registro la chat tra Sara e Maria...\n";
        registerChat.findChat(idSara, idMaria);
    } catch (const std::runtime_error& e) {
        std::cout << "Errore: "<< e.what()<<std::endl;
    }

    try {
        chat1.deleteMessage(1);  // Elimina il secondo messaggio
        chat1.showChat();  // Mostra la chat aggiornata
    } catch (const std::out_of_range& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nAggiungendo al registro la chat tra Maria e Sara...\n";
        registerChat.addChat(chat3);
    } catch (const std::exception& e) {
        std::cout<< e.what()<<std::endl;
    }

    return 0;
}
