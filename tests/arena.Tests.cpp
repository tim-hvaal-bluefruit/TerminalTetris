#include <gtest/gtest.h>
#include "arena.h"
#include "mockScreenBuffer.h"

class ArenaTests : public testing::Test
{
public:
    MockScreenBuffer mockScreenBuffer;
    Arena arena;
    ArenaTests() : arena(mockScreenBuffer) {}
};

TEST_F(ArenaTests, createArena_can_create_2_by_2_arena)
{
    // Given
    const int arenaHeight = 2, arenaWidth = 2;
    const char* expected = "##"
                           "##";

    // When Then
    const char* actual = arena.createArena(arenaHeight, arenaWidth);
    ASSERT_STREQ(actual, expected);
}

TEST_F(ArenaTests, createArena_can_create_3_by_3_arena)
{
    // Given
    const int arenaHeight = 3, arenaWidth = 3;
    const char* expected = "#.#"
                           "#.#"
                           "###";

    // When Then
    const char* actual = arena.createArena(arenaHeight, arenaWidth);
    ASSERT_STREQ(actual, expected);
}

TEST_F(ArenaTests, createArena_can_create_8_by_5_arena)
{
    // Given
    const int arenaHeight = 5, arenaWidth = 8;
    const char* expected = "#......#"
                           "#......#"
                           "#......#"
                           "#......#"
                           "########";

    // When Then
    const char* actual = arena.createArena(arenaHeight, arenaWidth);
    ASSERT_STREQ(actual, expected);
}

// TEST_F(ArenaTests, drawArena_draws_arena_to_screen_buffer)
// {
//     // Given
//     const int screenHeight = 8, screenWidth = 10;
//     mockScreenBuffer.setScreenBufferSize(screenHeight, screenWidth);

//     const int arenaHeight = 8, arenaWidth = 5;
//     arena.createArena(arenaHeight, arenaWidth);

//     const char* expectedScreen = "#......#.."
//                                  "#......#.."
//                                  "#......#.."
//                                  "#......#.."
//                                  "########.."
//                                  ".........."
//                                  ".........."
//                                  "..........";

//     // When
//     arena.drawArena();

//     // Then
//     ASSERT_STREQ(actualScreen, expectedScreen);
// }
