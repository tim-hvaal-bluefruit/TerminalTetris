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
    const int height = 2, width = 2;
    const wchar_t* expected = L"##"
                               "##";

    // When Then
    const wchar_t* actual = arena.createArena(height, width);
    ASSERT_STREQ(actual, expected);
}


TEST_F(ArenaTests, createArena_can_create_8_by_5_arena)
{
    // Given
    const int height = 5, width = 8;
    const wchar_t* expected = L"#      #"
                               "#      #"
                               "#      #"
                               "#      #"
                               "########";

    // When Then
    const wchar_t* actual = arena.createArena(height, width);
    ASSERT_STREQ(actual, expected);
}


TEST_F(ArenaTests, drawArena_passes_default_arena_to_screen_buffer)
{
    // Given
    arena.createArena();

    // When
    arena.drawArena();

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectSize, defaultArenaHeight * defaultArenaWidth);
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, defaultArenaHeight);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, defaultArenaWidth);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, defaultScreenOffsetX);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, defaultScreenOffsetY);
}

TEST_F(ArenaTests, drawArena_can_pass_specific_arena_size_to_screen_buffer)
{
    // Given
    const int h = 9, w = 9;
    arena.createArena(h, w);

    // When
    arena.drawArena();

    // Then
    ASSERT_EQ(mockScreenBuffer.mObjectSize, h * w);
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, h);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, w);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, defaultScreenOffsetX);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, defaultScreenOffsetY);
}

TEST_F(ArenaTests, addToArena_adds_blocks_to_the_fixed_arena)
{
    // Given
    const int h = 7, w = 6;
    arena.createArena(h, w);

    // When
    int height = 4, width = 4, arenaPosX = 1, arenaPosY = 2;
    wchar_t obj1[] = L"    "
                      " xx "
                      " x  "
                      " x  ";

    arena.addToArena(arena.getArena(), obj1, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected =  L"#    #"
                                "#    #"
                                "#    #"
                                "# xx #"
                                "# x  #"
                                "# x  #"
                                "######";

    ASSERT_STREQ(expected, arena.getArena());

    // When
    height = 4;
    width = 4;
    arenaPosX = 2;
    arenaPosY = 0;
    wchar_t obj2[] = L"    "
                      " OO "
                      " OO "
                      "    ";

    arena.addToArena(arena.getArena(), obj2, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected2 =  L"#    #"
                                 "#  OO#"
                                 "#  OO#"
                                 "# xx #"
                                 "# x  #"
                                 "# x  #"
                                 "######";

    ASSERT_STREQ(expected2, arena.getArena());
}


TEST_F(ArenaTests, drawCurrentPiece_adds_only_the_current_piece_to_the_screen)
{
    // Given
    const int h = 6, w = 8;
    arena.createArena(h, w);

    // When
    int height = 4, width = 4, arenaX = 1, arenaY = 1;
    const wchar_t* piece = L" X  "
                            " X  "
                            " X  "
                            " X  ";
    arena.drawCurrentPiece(piece, height, width, arenaX, arenaY);

    // Then
    const wchar_t* expected  =  L"#      #"
                                 "# X    #"
                                 "# X    #"
                                 "# X    #"
                                 "# X    #"
                                 "########";
    ASSERT_STREQ(expected, arena.getActiveArena());

    // When
    height = 4; width = 4; arenaX = 1; arenaY = 1;
    piece = L"    "
             "    "
             "XXXX"
             "    ";
    arena.drawCurrentPiece(piece, height, width, arenaX, arenaY);

    // Then
    expected  =  L"#      #"
                  "#      #"
                  "#      #"
                  "#XXXX  #"
                  "#      #"
                  "########";
    ASSERT_STREQ(expected, arena.getActiveArena());

    // ActiveArena is drawn to screen
    ASSERT_EQ(mockScreenBuffer.mObjectSize, h * w);
    ASSERT_EQ(mockScreenBuffer.mObjectHeight, h);
    ASSERT_EQ(mockScreenBuffer.mObjectWidth, w);
    ASSERT_EQ(mockScreenBuffer.mObjectXOffset, defaultScreenOffsetX);
    ASSERT_EQ(mockScreenBuffer.mObjectYOffset, defaultScreenOffsetY);
}
