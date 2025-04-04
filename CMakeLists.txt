cmake_minimum_required(VERSION 3.26)
project(Chat_Utenti)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR})
# Aggiungi i file sorgente principali
set(SOURCES
        User.cpp
        Message.cpp
        IdCreator.cpp
        Chat.cpp
        ChatRegister.cpp
)

# Aggiungi i file header
set(HEADERS
        User.h
        Message.h
        IdCreator.h
        Chat.h
        ChatRegister.h
)

# Crea l'eseguibile principale
add_executable(Chat_Utenti main.cpp ${SOURCES} ${HEADERS})

# Abilita GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Assicura che GoogleTest sia nei percorsi di inclusione
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Crea l'eseguibile per i test
add_executable(runTests Test/UserTest.cpp ${SOURCES} ${HEADERS}
        Test/MessageTest.cpp
        Test/ChatTest.cpp
        Test/ChatRegisterTest.cpp)

# Collega GoogleTest ai test
target_link_libraries(runTests GTest::gtest GTest::gtest_main)

# Abilita il framework di test
include(GoogleTest)
gtest_discover_tests(runTests)
