add_library(console)

target_sources(console
    PRIVATE console.cpp
)

target_include_directories(console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/interfaces
)