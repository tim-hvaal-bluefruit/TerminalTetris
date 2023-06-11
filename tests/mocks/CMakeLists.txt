add_library(mocks)
target_sources(mocks
    PRIVATE mockScreenBuffer.cpp
    PRIVATE mockArena.cpp
)

target_include_directories(mocks
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
)
