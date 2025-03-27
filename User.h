#include <iostream>
#include <utility>
#ifndef USER_H
#define USER_H

class User{
    public:
        User(const std::string& name);

        bool operator==(const User& other) const;

        const std::string& getName() const;
        int getId() const;
        void print() const;

    private:
        std::string name;
        int id;

};

#endif