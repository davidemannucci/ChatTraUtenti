#include "User.h"
#include "IdCreator.h"
#include <utility>

User:: User(const std::string& name) : name(name){
    id=IdCreator::createId();
}

const std::string& User::getName() const {
    return name;
}
int User::getId() const{
    return id;
}

void User::print() const {
    std::cout<<"Utente: "<<name<<" (Id associato: "<<id<<")"<<std::endl;
}

bool User::operator==(const User& other) const {
    return id == other.id;
}