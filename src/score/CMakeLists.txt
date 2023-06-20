add_library(score)

target_sources(score
    PRIVATE score.cpp
)

target_include_directories(score
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
)