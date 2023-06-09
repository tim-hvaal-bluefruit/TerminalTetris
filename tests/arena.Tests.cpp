#include <gtest/gtest.h>
#include "arena.h"
#include "mockScreenBuffer.h"

using namespace arena;
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
    const int height = 2, width = 2, xOffset = 0, yOffset = 0;
    const wchar_t* expected = L"##"
                               "##";

    // When Then
    const wchar_t* actual = arena.createArena(height, width, xOffset, yOffset);
    ASSERT_STREQ(actual, expected);
}


TEST_F(ArenaTests, createArena_can_create_8_by_5_arena)
{
    // Given
    const int height = 5, width = 8, xOffset = 0, yOffset = 0;
    const wchar_t* expected = L"#......#"
                               "#......#"
                               "#......#"
                               "#......#"
                               "########";

    // When Then
    const wchar_t* actual = arena.createArena(height, width, xOffset, yOffset);
    ASSERT_STREQ(actual, expected);
}

TEST_F(ArenaTests, drawArena_passes_arena_of_default_dimensions_to_screen_buffer)
{
    // Given
    arena.createArena();

    // When
    arena.drawArena();

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectSize, defaultArenaHeight * defaultArenaWidth);
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, defaultArenaHeight);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, defaultArenaWidth);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, defaultXOffset);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, defaultYOffset);
}

TEST_F(ArenaTests, drawArena_passes_specific_arena)
{
    // Given
    const int height = 9, width = 9, xOffset = 2, yOffset = 2;
    arena.createArena(height, width, xOffset, yOffset);

    // When
    arena.drawArena();

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectSize, height * width);
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, height);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, width);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, xOffset);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, yOffset);
}

TEST_F(ArenaTests, addToArena_adds_blocks_to_the_fixed_arena)
{
    // Given
    const int h = 7, w = 6, xOff = 0, yOff = 0;
    arena.createArena(h, w, xOff, yOff);

    // When
    int height = 4, width = 4, arenaPosX = 1, arenaPosY = 2;
    wchar_t obj[] = L"...."
                     ".xx."
                     ".x.."
                     ".x..";

    arena.addToArena(obj, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected =  L"#....#"
                                "#....#"
                                "#....#"
                                "#.xx.#"
                                "#.x..#"
                                "#.x..#"
                                "######";

    ASSERT_STREQ(expected, arena.getArena());

    // When
    height = 4;
    width = 4;
    arenaPosX = 2;
    arenaPosY = 0;
    wchar_t obj2[] = L"...."
                      ".OO."
                      ".OO."
                      "....";

    arena.addToArena(obj2, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected2 =  L"#....#"
                                 "#..OO#"
                                 "#..OO#"
                                 "#.xx.#"
                                 "#.x..#"
                                 "#.x..#"
                                 "######";

    ASSERT_STREQ(expected2, arena.getArena());
}
