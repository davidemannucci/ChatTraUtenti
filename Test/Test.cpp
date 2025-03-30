#include <gtest/gtest.h>
#include "User.h"
#include "IdCreator.h"
#include "Message.h"
#include "Chat.h"
#include "ChatRegister.h"

class UserTest : public ::testing::Test {
protected:
    void TearDown() override {
        IdCreator::reset();
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

TEST_F(UserTest, ConstructorSetsNameAndId) {
    User user("Marco");
    EXPECT_EQ(user.getName(), "Marco");
    EXPECT_GE(user.getId(), 1000);
    EXPECT_LE(user.getId(), 9999);
}

TEST_F(UserTest, IdWithinValidRange) {
    User user("Marco");
    EXPECT_GE(user.getId(), 1000);
    EXPECT_LE(user.getId(), 9999);
}

TEST_F(UserTest, HandlesEmptyUserName) {
    User user("");
    EXPECT_TRUE(user.getName().empty());
}

TEST_F(UserTest, ToStringFormat) {
    User user("Marco");
    std::string output = user.toStringUser();
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
    EXPECT_TRUE(output.find("Marco to Maria") != std::string::npos);
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
    EXPECT_GT(msg2.getTimestamp(), msg1.getTimestamp()); // Verifica incremento
}


class ChatTest : public ::testing::Test {
protected:
    User Marco{"Marco"};
    User Maria{"Maria"};
    Chat chat{"ChatTest", Marco, Maria};
    std::time_t now = std::time(nullptr);
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

TEST_F(ChatTest, ToStringShowsChatContent) {
    Chat chat("ChatTest", Marco, Maria);
    std::string output = chat.toStringChat();
    EXPECT_TRUE(output.find("ChatTest") != std::string::npos)
                        << "Output effettivo:\n" << output;
}

TEST_F(ChatTest, MarkMessageAsReadUpdatesCount) {
    chat.sendMessage(Message("Test", Marco, Maria));
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

class ChatRegisterTest : public ::testing::Test {
protected:
    User Marco{"Marco"};
    User Maria{"Maria"};
    Chat chat{"ChatRegisterTest", Marco, Maria};
    ChatRegister registry;
};

TEST_F(ChatRegisterTest, StoresChatsBySortedIDs) {
    registry.addChat(chat);
    auto& found = registry.findChat(Maria.getId(), Marco.getId());
    EXPECT_EQ(found.getUser1Id(), Marco.getId());
}

TEST_F(ChatRegisterTest, FindChatWorksWithSwappedIDs) {
    registry.addChat(chat);
    Chat& found = registry.findChat(Maria.getId(), Marco.getId());
    EXPECT_EQ(found.getChatName(), "ChatRegisterTest");
}

TEST_F(ChatRegisterTest, AddAndRetrieveChat) {
    registry.addChat(chat);
    Chat& found = registry.findChat(Marco.getId(), Maria.getId());
    EXPECT_EQ(found.getChatName(), "ChatRegisterTest");
}

TEST_F(ChatRegisterTest, DeletesChatsProperly) {
    registry.addChat(chat);
    EXPECT_NO_THROW(registry.findChat(Marco.getId(), Maria.getId()));
    registry.deleteChat(Marco.getId(), Maria.getId());
    EXPECT_THROW(registry.findChat(Marco.getId(), Maria.getId()), std::runtime_error);
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
