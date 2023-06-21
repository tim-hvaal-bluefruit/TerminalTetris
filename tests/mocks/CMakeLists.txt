add_library(mocks)
target_sources(mocks
    PRIVATE mockScreenBuffer.cpp
    PRIVATE mockArena.cpp
    PRIVATE mockPiece.cpp
    PRIVATE mockUserInput.cpp
    PRIVATE mockScore.cpp
    PRIVATE mockConsole.cpp
)

target_include_directories(mocks
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/userInput
    PRIVATE ${PROJECT_SOURCE_DIR}/src/score
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
)
