#include <gtest/gtest.h>
#include "User.h"
#include "Chat.h"
#include "ChatRegister.h"

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
    EXPECT_THROW(registry.addChat(chat), std::runtime_error);
}

TEST_F(ChatRegisterTest, FindNonexistentChatThrows) {
    EXPECT_THROW(registry.findChat(999, 1000), std::runtime_error);
}

TEST_F(ChatRegisterTest, DeleteNonexistentChatThrows) {
    EXPECT_THROW(registry.deleteChat(999, 1000), std::runtime_error);
}

TEST_F(ChatRegisterTest, PrintEmptyRegisterOutput) {
    testing::internal::CaptureStdout();
    registry.printRegister();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Il registro è vuoto!") != std::string::npos);
}