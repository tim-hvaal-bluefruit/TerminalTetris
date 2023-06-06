add_library(arena)

target_sources(arena
    PRIVATE arena.cpp
)

target_include_directories(arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
)