#include <gtest/gtest.h>
#include "arena.h"
#include "mockConsole.h"
#include "mockScreenBuffer.h"
#include "mockObserver.h"

using namespace arena;
class ArenaTests : public testing::Test
{
public:
    MockScreenBuffer mockScreenBuffer;
    MockConsole mockConsole;
    Arena arena;
    ArenaTests() :  arena(mockScreenBuffer, mockConsole) {}
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

TEST_F(ArenaTests, checkObjectFits_returns_false_if_object_overlaps_any_part_of_arena)
{
    // Given - clashing arena and object
    const int h = 3, w = 4;
    arena.createArena(h, w);

    const int height = 2, width = 2;
    const int arenaX = 0, arenaY = 0;
    const wchar_t* object = L"X"
                             " X";

    // When & Then
    bool objectFits = true;
    objectFits = arena.checkObjectFits(object, height, width, arenaX, arenaY);
    ASSERT_FALSE(objectFits);

    // X  # overlaps here
    // #X #
    // ####
}


TEST_F(ArenaTests, checkObjectFits_returns_true_if_object_is_clear_of_any_part_of_arena)
{
    // Given - clashing arena and object
    const int h = 3, w = 4;
    arena.createArena(h, w);

    const int height = 2, width = 2;
    const int arenaX = 1, arenaY = 0;
    const wchar_t* object = L"X"
                             " X";

    // When & Then
    bool objectFits = false;
    objectFits = arena.checkObjectFits(object, height, width, arenaX, arenaY);
    ASSERT_TRUE(objectFits);

    // #X # fits
    // # X#
    // ####
}


TEST_F(ArenaTests, check_line_returns_true_if_line_complete)
{
    // Given
    int height = 2, width = 5;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line = L"#xxx#";
    arena.addToArena(arena.getArena(), line, h, w, xPos, yPos);

    // When & Then
    ASSERT_TRUE(arena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, check_line_returns_false_if_line_incomplete)
{
    // Given
    int height = 2, width = 5;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line = L"#x x#";
    arena.addToArena(arena.getArena(), line, h, w, xPos, yPos);

    // When & Then
    ASSERT_FALSE(arena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, checkAllLines_returns_two_when_two_complete_lines)
{
    // Given
    int height = 3, width = 5;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    const wchar_t* line1 = L"#1111#";
    arena.addToArena(arena.getArena(), line0, h, w, xPos, yPos);
    arena.addToArena(arena.getArena(), line1, h, w, xPos, yPos + 1);

    // When & Then
    ASSERT_EQ(arena.checkAllLines(), 2);
}


TEST_F(ArenaTests, checkAllLines_returns_three_when_three_complete_lines_amongst_incomplete_lines)
{
    // Given
    int height = 6, width = 5;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    const wchar_t* line1 = L"# 111#";
    const wchar_t* line2 = L"#22 2#";
    const wchar_t* line3 = L"#3333#";
    const wchar_t* line4 = L"#4444#";
    arena.addToArena(arena.getArena(), line0, h, w, xPos, yPos);
    arena.addToArena(arena.getArena(), line1, h, w, xPos, yPos + 1);
    arena.addToArena(arena.getArena(), line2, h, w, xPos, yPos + 2);
    arena.addToArena(arena.getArena(), line3, h, w, xPos, yPos + 3);
    arena.addToArena(arena.getArena(), line4, h, w, xPos, yPos + 4);

    // When & Then
    ASSERT_EQ(arena.checkAllLines(), 3);
}


TEST_F(ArenaTests, destroyLine_sets_each_line_char_to_blankchar)
{
    // Given
    int height = 2, width = 5;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    arena.addToArena(arena.getArena(), line0, h, w, xPos, yPos);

    // When
    arena.destroyLine(yPos);

    // Then
    ASSERT_FALSE(arena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, animate_for_100ms_passes_delay_to_console)
{
    // Given
    const int expectedFrameLengthMs = 100;

    // When & Then
    arena.animate(expectedFrameLengthMs);
    ASSERT_EQ(mockConsole.mFrameLengthMs, expectedFrameLengthMs);
}


TEST_F(ArenaTests, moveStackDown_moves_the_whole_stack_down_by_one_line_at_a_given_line)
{
    // Given
    int height = 4, width = 6;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#00 0#";
    const wchar_t* row1 = L"#1 11#";
    const wchar_t* row2 = L"#2222#";
    arena.addToArena(arena.getArena(), row0, h, w, xPos, yPos);
    arena.addToArena(arena.getArena(), row1, h, w, xPos, yPos + 1);
    arena.addToArena(arena.getArena(), row2, h, w, xPos, yPos + 2);

    // When
    int completeRowPosY = yPos + 2;
    arena.moveStackDown(completeRowPosY);

    // Then
    const wchar_t * expectedArena = L"#    #"
                                     "#00 0#"
                                     "#1 11#"
                                     "######";

    ASSERT_STREQ(arena.getArena(), expectedArena);
}


TEST_F(ArenaTests, checkAllLines_does_not_notify_with_no_complete_lines)
{
    // Given
    MockObserver mockObserver;
    arena.addObserver(&mockObserver, Event::linesCompleted);

    int height = 3, width = 6;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#00 0#";
    const wchar_t* row1 = L"#1 11#";
    arena.addToArena(arena.getArena(), row0, h, w, xPos, yPos);
    arena.addToArena(arena.getArena(), row1, h, w, xPos, yPos + 1);

    // When
    arena.checkAllLines();

    // Then
    ASSERT_EQ(mockObserver.mCallCount, 0);
}


TEST_F(ArenaTests, checkAllLines_notifies_on_complete_lines)
{
    // Given
    MockObserver mockObserver;
    arena.addObserver(&mockObserver, Event::linesCompleted);

    int height = 3, width = 6;
    arena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#0000#";
    const wchar_t* row1 = L"#1111#";
    arena.addToArena(arena.getArena(), row0, h, w, xPos, yPos);
    arena.addToArena(arena.getArena(), row1, h, w, xPos, yPos + 1);

    // When
    arena.checkAllLines(); // 2 complete lines

    // Then
    ASSERT_EQ(mockObserver.mCallCount, 1);
    ASSERT_EQ(mockObserver.mValue, 2);
}