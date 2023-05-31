add_executable(AllTests)

target_sources(AllTests
    PRIVATE draw.Tests.cpp
    PRIVATE console.Tests.cpp
)

target_include_directories(AllTests
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(AllTests
    tetris
    GTest::gtest_main
)
