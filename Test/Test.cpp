#include <gtest/gtest.h>
#include "User.h"
#include "IdCreator.h"
#include "Message.h"
#include "Chat.h"
#include "ChatRegister.h"

class UserTest : public ::testing::Test {
protected:
    void TearDown() override {
        IdCreator::idUsed.clear();
    }
};

TEST_F(UserTest, GeneratesUniqueIDs) {
User user1("Marco");
User user2("Maria");
EXPECT_NE(user1.getId(), user2.getId());
}

TEST_F(UserTest, EqualityChecksIDNotName) {
User user1("Marco");
User user2("Marco");
EXPECT_FALSE(user1 == user2);
}

TEST_F(UserTest, EqualityBasedOnIdOnly) {
    User user1("Marco");
    User user2("Marco"); // Stesso nome, ID diverso
    EXPECT_NE(user1.getId(), user2.getId());
    EXPECT_FALSE(user1 == user2);
}

TEST_F(UserTest, ConstructorSetsNameAndId) {
    User user("Marco");
    EXPECT_EQ(user.getName(), "Marco");
    EXPECT_GE(user.getId(), 1000);
    EXPECT_LE(user.getId(), 9999);
}

TEST_F(UserTest, PrintOutputFormat) {
    User user("Marco");
    testing::internal::CaptureStdout();
    user.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Utente: Marco (Id associato: ") != std::string::npos);
}

class MessageTest : public ::testing::Test {
protected:
    User sender{"Marco"};
    User receiver{"Maria"};
    std::time_t fixed_time = 1700000000; // 14/11/2023 22:13:20 UTC

    void SetUp() override {
        Message::setTimeProvider([this]() { return fixed_time; });
        Message::resetTimeProvider(); // Resetta lastTime
        Message::setTimeProvider([this]() { return fixed_time; }); // Reimposta
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

TEST_F(MessageTest, PrintMessageReadStatus) {
    Message msg("Test", sender, receiver);
    msg.markAsRead();
    testing::internal::CaptureStdout();
    msg.printMessage();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("(Read)") != std::string::npos);
}

TEST_F(MessageTest, ReadStatusInitializedToFalse) {
    Message msg("Test", sender, receiver);
    EXPECT_FALSE(msg.getReadStatus());
}

TEST_F(MessageTest, AssignmentOperatorCopiesAllFields) {
    Message original("Original", sender, receiver);
    original.markAsRead();
    Message copy;
    copy = original;
    EXPECT_EQ(copy.getText(), "Original");
    EXPECT_TRUE(copy.getReadStatus());
}

TEST_F(MessageTest, RandomTimestampIncrement) {
    Message::resetTimeProvider();
    Message::setTimeProvider([]() { return 1000; });
    Message msg1("Msg1", sender, receiver);
    Message msg2("Msg2", sender, receiver);
    EXPECT_GT(msg2.getTimestamp(), msg1.getTimestamp()); // Verifica incremento
}


class ChatTest : public ::testing::Test {
protected:
    User Marco{"Marco"};
    User Maria{"Maria"};
    Chat chat{Marco, Maria};
    std::time_t now = std::time(nullptr);
};

TEST_F(ChatTest, AddsMessagesCorrectly) {
    chat.sendMessage(Message("Ciao", Marco, Maria));
    EXPECT_EQ(chat.chatMessages.size(), 1);
}

TEST_F(ChatTest, DeletesMessagesSafely) {
    chat.sendMessage(Message("Hello", Marco, Maria));
    chat.deleteMessage(0);
    EXPECT_TRUE(chat.chatMessages.empty());

    EXPECT_THROW(chat.deleteMessage(-1), std::out_of_range);
    EXPECT_THROW(chat.deleteMessage(100), std::out_of_range);
}

TEST_F(ChatTest, ShowEmptyChatOutput) {
    testing::internal::CaptureStdout();
    chat.showChat();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Chat tra Marco e Maria") != std::string::npos);
    EXPECT_TRUE(output.find("-----------------------") != std::string::npos);
}

TEST_F(ChatTest, PrintChatInfoFormat) {
    testing::internal::CaptureStdout();
    chat.printChatInfo();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Chat tra Marco (ID: ") != std::string::npos);
}

class ChatRegisterTest : public ::testing::Test {
protected:
    User Marco{"Marco"};
    User Maria{"Maria"};
    Chat chat{Marco, Maria};
    ChatRegister registry;
};

TEST_F(ChatRegisterTest, StoresChatsBySortedIDs) {
    registry.addChat(chat);
    auto& found = registry.findChat(Maria.getId(), Marco.getId());
    EXPECT_EQ(found.user1.getId(), Marco.getId());
}

TEST_F(ChatRegisterTest, DeletesChatsProperly) {
    registry.addChat(chat);
    registry.deleteChat(Marco.getId(), Maria.getId());
    EXPECT_TRUE(registry.chats.empty());
}

TEST_F(ChatRegisterTest, AddDuplicateChatThrows) {
    registry.addChat(chat);
    EXPECT_THROW(registry.addChat(chat), std::runtime_error); // Testa eccezione duplicati
}

TEST_F(ChatRegisterTest, FindNonexistentChatThrows) {
    EXPECT_THROW(registry.findChat(999, 1000), std::runtime_error); // Testa chat inesistente
}

TEST_F(ChatRegisterTest, DeleteNonexistentChatThrows) {
    EXPECT_THROW(registry.deleteChat(999, 1000), std::runtime_error); // Testa cancellazione chat inesistente
}

TEST_F(ChatRegisterTest, PrintEmptyRegisterOutput) {
    testing::internal::CaptureStdout();
    registry.printRegister();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Il registro è vuoto!") != std::string::npos);
}