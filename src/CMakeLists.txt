add_subdirectory(arena)
add_subdirectory(console)
add_subdirectory(screenBuffer)
add_subdirectory(piece)

add_executable(tetris)

target_sources(tetris
    PRIVATE main.cpp
)

target_include_directories(tetris
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
)


target_link_libraries(tetris
    console
    screenBuffer
    piece
    arena
)
