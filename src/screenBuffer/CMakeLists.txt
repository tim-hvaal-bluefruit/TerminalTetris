add_library(screenBuffer)

target_sources(screenBuffer
    PRIVATE screenBuffer.cpp
)

target_include_directories(screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/piece
    PRIVATE ${PROJECT_SOURCE_DIR}/src/interfaces
)