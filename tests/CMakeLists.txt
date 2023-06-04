add_subdirectory(mocks)

add_executable(AllTests)

target_sources(AllTests
    PRIVATE console.Tests.cpp
    PRIVATE screenBuffer.Tests.cpp
    PRIVATE arena.Tests.cpp
)

target_include_directories(AllTests
    PRIVATE ${PROJECT_SOURCE_DIR}/src/screenBuffer
    PRIVATE ${PROJECT_SOURCE_DIR}/src/console
    PRIVATE ${PROJECT_SOURCE_DIR}/src/arena
    PRIVATE ${PROJECT_SOURCE_DIR}/tests/mocks
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(AllTests
    mocks
    console
    screenBuffer
    arena
    GTest::gtest_main
)
