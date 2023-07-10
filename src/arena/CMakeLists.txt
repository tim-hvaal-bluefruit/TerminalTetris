add_library(arena)

target_sources(arena
    PRIVATE arena.cpp
)

target_include_directories(arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/interfaces
    PRIVATE ${PROJECT_SOURCE_DIR}/src/observers
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
)