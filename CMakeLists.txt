cmake_minimum_required(VERSION 3.10)
project(TerminalTetris)

# In FetchContent, set timestamp of extracted files to the time of extraction
cmake_policy(SET CMP0135 NEW)

include(fetchContent)
FetchContent_Declare(
    googleTest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(src/application)

add_subdirectory(src/arena)
add_subdirectory(src/console)
add_subdirectory(src/game)
add_subdirectory(src/piece)
add_subdirectory(src/score)
add_subdirectory(src/screenBuffer)
add_subdirectory(src/userInput)

add_subdirectory(tests)
