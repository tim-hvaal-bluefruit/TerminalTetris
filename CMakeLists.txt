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

add_subdirectory(src)
add_subdirectory(tests)

# TODO every time i change anything in a cmake list it does a rebuild - where is this setting?
# TODO why do i have to include fetchContent? - is this like a switch?
# TODO why gtest forced shared crt
# TODO research fetch content declare, and make available - which adds gtest to _deps?
# TODO why policy change? - remove the line to see the warning