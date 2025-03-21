#include <iostream>
#include <utility>
#ifndef USER_H
#define USER_H

class User{
public:
    std::string name;
    int id;

    User(const std::string& name);
    User()=default;

    bool operator==(const User& other) const;

    const std::string& getName() const;
    int getId() const;
    void print() const;
};

#endif