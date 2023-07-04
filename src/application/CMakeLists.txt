add_executable(application)

target_sources(application
    PRIVATE application.cpp
    PRIVATE instantiation.cpp
    PRIVATE main.cpp
)

target_include_directories(application
    PRIVATE ${PROJECT_SOURCE_DIR}/src/application
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/game
    PRIVATE ${PROJECT_SOURCE_DIR}/src/observers
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/score
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/userInput
    PRIVATE ${PROJECT_SOURCE_DIR}/src/interfaces
)

target_link_libraries(application
    arena
    console
    game
    piece
    score
    screenBuffer
    userInput
)