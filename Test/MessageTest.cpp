#include <gtest/gtest.h>
#include "User.h"
#include "Message.h"

class MessageTest : public ::testing::Test {
protected:
    User sender{"Marco"};
    User receiver{"Maria"};
    std::time_t fixed_time = 1700000000;

    void SetUp() override {
        Message::setTimeProvider([this]() { return fixed_time; });
        Message::resetTimeProvider();
        Message::setTimeProvider([this]() { return fixed_time; });
    }

    void TearDown() override {
        Message::resetTimeProvider();
    }
};

TEST_F(MessageTest, GeneratesCorrectBaseTimestamp) {
    Message msg("Hello", sender, receiver);
    EXPECT_EQ(msg.getTimestamp(), "2023-11-14 22:13:20");
}

TEST_F(MessageTest, CopySemanticsPreserveTimestamp) {
    Message original("Original", sender, receiver);
    Message copy(original);
    EXPECT_EQ(original.getTimestamp(), copy.getTimestamp());
    EXPECT_EQ(original.getText(), copy.getText());
}

TEST_F(MessageTest, HandlesEmptyMessageText) {
    Message msg("", sender, receiver);
    EXPECT_TRUE(msg.getText().empty());
}

TEST_F(MessageTest, ToStringIncludesTimestamp) {
    Message msg("Hello", sender, receiver);
    std::string output = msg.toStringMessage();
    EXPECT_TRUE(output.find("2023-11-14 22:13:20") != std::string::npos);
}

TEST_F(MessageTest, ToStringShowsReadStatus) {
    Message msg("Hello", sender, receiver);
    msg.markAsRead();
    std::string output = msg.toStringMessage();
    EXPECT_TRUE(output.find("(Read)") != std::string::npos);
}

TEST_F(MessageTest, ToStringFullFormat) {
    Message msg("Ciao!", sender, receiver);
    std::string output = msg.toStringMessage();
    EXPECT_TRUE(output.find("[2023-11-14 22:13:20] Marco to Maria : Ciao! (Not Read)") != std::string::npos);
}

TEST_F(MessageTest, AssignmentOperatorCopiesAllFields) {
    User sender("Marco");
    User receiver("Maria");
    Message original("Original", sender, receiver);
    original.markAsRead();
    Message copy = original;
    EXPECT_EQ(copy.getText(), "Original");
    EXPECT_TRUE(copy.isRead());
}

TEST_F(MessageTest, RandomTimestampIncrement) {
    Message::resetTimeProvider();
    Message::setTimeProvider([]() { return 1000; });
    Message msg1("Msg1", sender, receiver);
    Message msg2("Msg2", sender, receiver);
    EXPECT_GT(msg2.getTimestamp(), msg1.getTimestamp());
}