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


