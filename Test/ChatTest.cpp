#include <gtest/gtest.h>
#include "User.h"
#include "Chat.h"
#include "Message.h"

class ChatTest : public ::testing::Test {
protected:
    User Marco{"Marco"};
    User Maria{"Maria"};
    Chat chat{"ChatTest", Marco, Maria};
};

TEST_F(ChatTest, AddsMessagesCorrectly) {
    chat.sendMessage(Message("Ciao", Marco, Maria));
    EXPECT_EQ(chat.getTotalMessages(), 1);
}

TEST_F(ChatTest, GetChatNameReturnsCorrectName) {
    EXPECT_EQ(chat.getChatName(), "ChatTest");
}

TEST_F(ChatTest, DeletesMessagesSafely) {
    chat.sendMessage(Message("Hello", Marco, Maria));
    chat.deleteMessage(0);
    EXPECT_EQ(chat.getTotalMessages(), 0);
    EXPECT_THROW(chat.deleteMessage(-1), std::out_of_range);
}

TEST_F(ChatTest, ToStringShowsCorrectFormatWhenEmpty) {
    std::string output = chat.toStringChat();
    EXPECT_TRUE(output.find("Nome chat: ChatTest") != std::string::npos);
    EXPECT_TRUE(output.find("-----------------------") != std::string::npos);
}

TEST_F(ChatTest, MarkMessageAsReadUpdatesCount) {
    chat.sendMessage(Message("Test", Marco, Maria));
    EXPECT_EQ(chat.getUnreadMessageCount(), 1);
    chat.markMessageAsRead(0);
    EXPECT_EQ(chat.getUnreadMessageCount(), 0);
}

TEST_F(ChatTest, UnreadMessagesCounter) {
    chat.sendMessage(Message("Msg1", Marco, Maria));
    chat.sendMessage(Message("Msg2", Maria, Marco));
    EXPECT_EQ(chat.getUnreadMessageCount(), 2);
    chat.markMessageAsRead(0);
    EXPECT_EQ(chat.getUnreadMessageCount(), 1);
}

TEST_F(ChatTest, GetMessageWorksCorrectly) {
    chat.sendMessage(Message("Primo messaggio", Marco, Maria));
    chat.sendMessage(Message("Secondo messaggio", Maria, Marco));

    const Message& msg1 = chat.getMessage(0);
    EXPECT_EQ(msg1.getText(), "Primo messaggio");
    EXPECT_EQ(msg1.getSender().getName(), "Marco");

    const Message& msg2 = chat.getMessage(1);
    EXPECT_EQ(msg2.getText(), "Secondo messaggio");
    EXPECT_EQ(msg2.getSender().getName(), "Maria");

    // Test eccezioni
    EXPECT_THROW(chat.getMessage(-1), std::out_of_range);
    EXPECT_THROW(chat.getMessage(2), std::out_of_range);
}