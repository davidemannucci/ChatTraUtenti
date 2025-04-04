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
