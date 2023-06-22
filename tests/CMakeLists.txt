add_subdirectory(mocks)

add_executable(AllTests)

target_sources(AllTests
    PRIVATE console.Tests.cpp
    PRIVATE screenBuffer.Tests.cpp
    PRIVATE arena.Tests.cpp
    PRIVATE piece.Tests.cpp
    PRIVATE userInput.Tests.cpp
    PRIVATE game.Tests.cpp
    PRIVATE score.Tests.cpp
    PRIVATE observer.Tests.cpp
)

target_include_directories(AllTests
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/userInput
    PRIVATE ${PROJECT_SOURCE_DIR}/src/game
    PRIVATE ${PROJECT_SOURCE_DIR}/src/score
    PRIVATE ${PROJECT_SOURCE_DIR}/src/observers
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/mocks
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(AllTests
    mocks
    console
    screenBuffer
    arena
    piece
    userInput
    game
    score
    GTest::gtest_main
)
