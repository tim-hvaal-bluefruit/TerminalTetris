#include <gtest/gtest.h>
#include "arena.h"
#include "mockConsole.h"
#include "mockScreenBuffer.h"
#include "mockObserver.h"

using namespace arena;


class ArenaTestObject : public Arena
{
public:
    ArenaTestObject(MockScreenBuffer& mockScreenBuffer, MockConsole& mockConsole) :
        Arena(mockScreenBuffer, mockConsole)
    {}

    int& arenaHeight = mArenaHeight;
    int& arenaWidth = mArenaWidth;
    wchar_t* arena = mArena;
    wchar_t* activeArena = mActiveArena;
};


class ArenaTests : public testing::Test
{
public:
    MockScreenBuffer mockScreenBuffer;
    MockConsole mockConsole;
    ArenaTestObject mArena;
    ArenaTests() :  mArena(mockScreenBuffer, mockConsole) {}
};


TEST_F(ArenaTests, createArena_can_create_different_sized_arenas)
{
    // Given
    int height = 2, width = 2;
    const wchar_t* expected = L"##"
                               "##";

    // When Then
    const wchar_t* actual = mArena.createArena(height, width);
    ASSERT_STREQ(actual, expected);

    // Given
    height = 5, width = 8;
    expected = L"#      #"
                "#      #"
                "#      #"
                "#      #"
                "########";

    // When Then
    actual = mArena.createArena(height, width);
    ASSERT_STREQ(actual, expected);
}


TEST_F(ArenaTests, drawArena_passes_default_arena_to_screen_buffer)
{
    // Given
    mArena.createArena();

    // When
    mArena.drawArena();

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
    mArena.createArena(h, w);

    // When
    mArena.drawArena();

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
    mArena.createArena(h, w);

    // When
    int height = 4, width = 4, arenaPosX = 1, arenaPosY = 2;
    wchar_t obj1[] = L"    "
                      " xx "
                      " x  "
                      " x  ";
    mArena.addToArena(mArena.arena, obj1, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected =  L"#    #"
                                "#    #"
                                "#    #"
                                "# xx #"
                                "# x  #"
                                "# x  #"
                                "######";
    ASSERT_STREQ(expected, mArena.arena);


    // When
    height = 4;
    width = 4;
    arenaPosX = 2;
    arenaPosY = 0;
    wchar_t obj2[] = L"    "
                      " OO "
                      " OO "
                      "    ";
    mArena.addToArena(mArena.arena, obj2, height, width, arenaPosX, arenaPosY);

    // Then
    const wchar_t* expected2 =  L"#    #"
                                 "#  OO#"
                                 "#  OO#"
                                 "# xx #"
                                 "# x  #"
                                 "# x  #"
                                 "######";
    ASSERT_STREQ(expected2, mArena.arena);
}


TEST_F(ArenaTests, drawCurrentPiece_adds_just_the_current_piece_to_the_active_arena)
{
    // Given
    const int h = 6, w = 8;
    mArena.createArena(h, w);

    // When
    int height = 4, width = 4, arenaX = 1, arenaY = 1;
    const wchar_t* piece = L" X  "
                            " X  "
                            " X  "
                            " X  ";
    mArena.drawCurrentPiece(piece, height, width, arenaX, arenaY);

    // Then
    const wchar_t* expected  =  L"#      #"
                                 "# X    #"
                                 "# X    #"
                                 "# X    #"
                                 "# X    #"
                                 "########";
    ASSERT_STREQ(expected, mArena.activeArena);


    // When
    height = 4; width = 4; arenaX = 1; arenaY = 1;
    piece = L"    "
             "    "
             "XXXX"
             "    ";
    mArena.drawCurrentPiece(piece, height, width, arenaX, arenaY);

    // Then
    expected  =  L"#      #"
                  "#      #"
                  "#      #"
                  "#XXXX  #"
                  "#      #"
                  "########";
    ASSERT_STREQ(expected, mArena.activeArena);

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
    mArena.createArena(h, w);

    const int height = 2, width = 2;
    const int arenaX = 0, arenaY = 0;
    const wchar_t* object = L"X"
                             " X";

    // When & Then
    bool objectFits = true;
    objectFits = mArena.checkObjectFits(object, height, width, arenaX, arenaY);
    ASSERT_FALSE(objectFits);

    // X  # overlaps here
    // #X #
    // ####
}


TEST_F(ArenaTests, checkObjectFits_returns_true_if_object_is_clear_of_any_part_of_arena)
{
    // Given - object fits with arena
    const int h = 3, w = 4;
    mArena.createArena(h, w);

    const int height = 2, width = 2;
    const int arenaX = 1, arenaY = 0;
    const wchar_t* object = L"X"
                             " X";

    // When & Then
    bool objectFits = false;
    objectFits = mArena.checkObjectFits(object, height, width, arenaX, arenaY);
    ASSERT_TRUE(objectFits);

    // #X # fits
    // # X#
    // ####
}


TEST_F(ArenaTests, check_line_returns_true_if_line_complete)
{
    // Given
    int height = 2, width = 5;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line = L"#xxx#";
    mArena.addToArena(mArena.arena, line, h, w, xPos, yPos);

    // When & Then
    ASSERT_TRUE(mArena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, check_line_returns_false_if_line_incomplete)
{
    // Given
    int height = 2, width = 5;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line = L"#x x#";
    mArena.addToArena(mArena.arena, line, h, w, xPos, yPos);

    // When & Then
    ASSERT_FALSE(mArena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, checkAllLines_returns_two_when_two_complete_lines)
{
    // Given
    int height = 3, width = 5;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    const wchar_t* line1 = L"#1111#";
    mArena.addToArena(mArena.arena, line0, h, w, xPos, yPos);
    mArena.addToArena(mArena.arena, line1, h, w, xPos, yPos + 1);

    // When & Then
    ASSERT_EQ(mArena.checkAllLines(), 2);
}


TEST_F(ArenaTests, checkAllLines_returns_three_when_three_complete_lines_amongst_incomplete_lines)
{
    // Given
    int height = 6, width = 5;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    const wchar_t* line1 = L"# 111#";
    const wchar_t* line2 = L"#22 2#";
    const wchar_t* line3 = L"#3333#";
    const wchar_t* line4 = L"#4444#";
    mArena.addToArena(mArena.arena, line0, h, w, xPos, yPos);
    mArena.addToArena(mArena.arena, line1, h, w, xPos, yPos + 1);
    mArena.addToArena(mArena.arena, line2, h, w, xPos, yPos + 2);
    mArena.addToArena(mArena.arena, line3, h, w, xPos, yPos + 3);
    mArena.addToArena(mArena.arena, line4, h, w, xPos, yPos + 4);

    // When & Then
    ASSERT_EQ(mArena.checkAllLines(), 3);
}


TEST_F(ArenaTests, destroyLine_sets_each_line_char_to_blankchar)
{
    // Given
    int height = 2, width = 5;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* line0 = L"#0000#";
    mArena.addToArena(mArena.arena, line0, h, w, xPos, yPos);

    // When
    mArena.destroyLine(yPos);

    // Then
    ASSERT_FALSE(mArena.checkLineComplete(yPos));
}


TEST_F(ArenaTests, animate_for_100ms_passes_delay_to_console)
{
    // Given
    const int expectedFrameLengthMs = 100;

    // When & Then
    mArena.animate(expectedFrameLengthMs);
    ASSERT_EQ(mockConsole.mFrameLengthMs, expectedFrameLengthMs);
}


TEST_F(ArenaTests, moveStackDown_moves_the_whole_stack_down_by_one_line_at_a_given_line)
{
    // Given
    int height = 4, width = 6;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#00 0#";
    const wchar_t* row1 = L"#1 11#";
    const wchar_t* row2 = L"#2222#";
    mArena.addToArena(mArena.arena, row0, h, w, xPos, yPos);
    mArena.addToArena(mArena.arena, row1, h, w, xPos, yPos + 1);
    mArena.addToArena(mArena.arena, row2, h, w, xPos, yPos + 2);

    // When
    int completeRowPosY = yPos + 2;
    mArena.moveStackDown(completeRowPosY);

    // Then
    const wchar_t * expectedArena = L"#    #"
                                     "#00 0#"
                                     "#1 11#"
                                     "######";

    ASSERT_STREQ(mArena.getArena(), expectedArena);
}


TEST_F(ArenaTests, checkAllLines_does_not_notify_with_no_complete_lines)
{
    // Given
    MockObserver mockObserver;
    mArena.addObserver(&mockObserver, Event::linesCompleted);

    int height = 3, width = 6;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#00 0#";
    const wchar_t* row1 = L"#1 11#";
    mArena.addToArena(mArena.getArena(), row0, h, w, xPos, yPos);
    mArena.addToArena(mArena.getArena(), row1, h, w, xPos, yPos + 1);

    // When
    mArena.checkAllLines();

    // Then
    ASSERT_EQ(mockObserver.mCallCount, 0);
}


TEST_F(ArenaTests, checkAllLines_notifies_on_complete_lines)
{
    // Given
    MockObserver mockObserver;
    mArena.addObserver(&mockObserver, Event::linesCompleted);

    int height = 3, width = 6;
    mArena.createArena(height, width);

    const int h = 1, w = 5, xPos = 0, yPos = 0;
    const wchar_t* row0 = L"#0000#";
    const wchar_t* row1 = L"#1111#";
    mArena.addToArena(mArena.arena, row0, h, w, xPos, yPos);
    mArena.addToArena(mArena.arena, row1, h, w, xPos, yPos + 1);

    // When
    mArena.checkAllLines(); // 2 complete lines

    // Then
    ASSERT_EQ(mockObserver.mCallCount, 1);
    ASSERT_EQ(mockObserver.mValue, 2);
}


TEST_F(ArenaTests, on_construction_arena_registers_as_draw_item_with_screen_buffer)
{
    ASSERT_EQ(mockScreenBuffer.mNumRegisteredDrawItems, 1);
}


TEST_F(ArenaTests, arena_draw_method_draws_arena_to_screenBuffer)
{
    // Given
    ASSERT_EQ(mockScreenBuffer.mCallCount, 0);

    // When Then
    mArena.draw();
    ASSERT_EQ(mockScreenBuffer.mCallCount, 1);
}
