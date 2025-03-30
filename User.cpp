#include "User.h"
#include "IdCreator.h"
#include <utility>
#include <sstream>

User:: User(const std::string& name) : name(name){
    id=IdCreator::createId();
}

const std::string& User::getName() const {
    return name;
}
int User::getId() const{
    return id;
}

std::string User::toStringUser() const {
    std::stringstream ss;
    ss << "Utente: " << name << " (Id associato: " << id << ")";
    return ss.str();
}


bool User::operator==(const User& other) const {
    return id == other.id;
}