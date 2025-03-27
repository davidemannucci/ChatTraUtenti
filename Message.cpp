#include "Message.h"
#include <chrono>
#include <random>
#include <iomanip>
#include <sstream>

std::function<std::time_t()> Message::timeProvider = []() {
    return std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
    );
};

std::time_t Message::lastTime = 0;

Message::Message(const std::string& text, User& sender, User& addressee) : text(text), sender(sender), addressee(addressee), isRead(false){

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 14400);

    // Genera intervallo casuale
    std::time_t currentTime = timeProvider();
    if(lastTime == 0) lastTime = currentTime;
    else lastTime += dist(rng);

    timestamp = generateTimestamp(lastTime);
}

void Message::setTimeProvider(std::function<std::time_t()> provider) {
    timeProvider = provider;
    lastTime = 0;
}

void Message::resetTimeProvider() {
    timeProvider = []() {
        return std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now()
        );
    };
    lastTime = 0;
}

std::string Message::generateTimestamp(std::time_t baseTime) {
    std::tm ptm;

#ifdef _WIN32
    gmtime_s(&ptm, &baseTime);
#else
    gmtime_r(&baseTime, &ptm);
#endif

    std::stringstream ss;
    ss << std::put_time(&ptm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Message::Message(const Message& other)
        : text(other.text), sender(other.sender),
          addressee(other.addressee), timestamp(other.timestamp), isRead(other.isRead) {}

Message& Message::operator=(const Message& other) {
    if(this != &other) {
        text = other.text;
        sender = other.sender;
        addressee = other.addressee;
        timestamp = other.timestamp;
        isRead = other.isRead;
    }
    return *this;
}

const std::string& Message::getText() const { return text; }
const User& Message::getSender() const { return sender; }
const User& Message::getAddressee() const { return addressee; }
const std::string& Message::getTimestamp() const { return timestamp; }

void Message::markAsRead() {
    isRead = true;
}

bool Message::getIsRead() const{
    return isRead;
}

void Message::printMessage() const {
    std::cout << "[" << timestamp << "] "
              << sender.getName() << " to "
              << addressee.getName() << " : "<<text<< (getIsRead() ? " (Read)" : " (Not Read)") << std::endl;
}