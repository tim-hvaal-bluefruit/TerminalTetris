add_library(game)

target_sources(game
    PRIVATE game.cpp
)

target_include_directories(game
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/userInput
    PRIVATE ${PROJECT_SOURCE_DIR}/src/score
)