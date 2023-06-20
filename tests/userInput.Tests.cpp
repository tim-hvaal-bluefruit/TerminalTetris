#include <gtest/gtest.h>
#include "userInput.h"
#include "mockPiece.h"

using namespace userInput;
using namespace piece;

class UserInputTests : public ::testing::Test
{
public:
	UserInputTests()
		: userInput(mockPiece)
	{}

	MockPiece mockPiece;
	UserInput userInput;
};

TEST_F(UserInputTests, user_input_is_detected)
{
	//TODO - mock out windows api input
	//getUserInput() makes a windows API call
}


TEST_F(UserInputTests, user_input_stored_and_retrieved)
{
    // When Then
    userInput.setIsKeyPressed(Key::left, true);
    userInput.setIsKeyPressed(Key::right, true);
    userInput.setIsKeyPressed(Key::down, true);
    ASSERT_TRUE(userInput.getIsKeyPressed(Key::left));
    ASSERT_TRUE(userInput.getIsKeyPressed(Key::right));
    ASSERT_TRUE(userInput.getIsKeyPressed(Key::down));

    // When Then
    userInput.setIsKeyPressed(Key::down, false);
    ASSERT_FALSE(userInput.getIsKeyPressed(Key::down));
}


TEST_F(UserInputTests, move_passes_move_direction_to_piece)
{
	// Given
	userInput.setIsKeyPressed(Key::left, true);
    userInput.setIsKeyPressed(Key::right, true);
    userInput.setIsKeyPressed(Key::down, true);
    userInput.setIsKeyPressed(Key::rotate, true);

    // When Then
	userInput.move();

    ASSERT_TRUE(mockPiece.mMoveLeftCalled);
    ASSERT_TRUE(mockPiece.mMoveRightCalled);
    ASSERT_TRUE(mockPiece.mMoveDownCalled);
    ASSERT_TRUE(mockPiece.mRotateCalled);
}

