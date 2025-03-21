#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <ctime>
#include <functional>
#include "User.h"

class Message {
private:
    static std::function<std::time_t()> timeProvider;
    static std::time_t lastTime;

    std::string text;
    User sender;
    User addressee;
    std::string timestamp;
    bool isRead;

    std::string generateTimestamp(std::time_t baseTime);

public:
    Message(const std::string& text, User& sender, User& addressee);
    Message() = default;
    Message(const Message& other);

    // Interface per i test
    static void setTimeProvider(std::function<std::time_t()> provider);
    static void resetTimeProvider();

    // Getters
    const std::string& getText() const;
    const User& getSender() const;
    const User& getAddressee() const;
    const std::string& getTimestamp() const;
    void markAsRead();
    bool getReadStatus() const;
    void printMessage() const;

    Message& operator=(const Message& other);
};

#endif