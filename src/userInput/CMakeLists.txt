add_library(userInput)

target_sources(userInput
    PRIVATE userInput.cpp
)

target_include_directories(userInput
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
)