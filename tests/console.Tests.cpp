#include <gtest/gtest.h>
#include "console.h"
#include "mockScreenBuffer.h"

using namespace screenBuffer;


TEST(consoleTests, copy_screen_to_console__copies_buffer_to_std_out)
{
    //Given
    MockScreenBuffer mockBuffer;
    mockBuffer.fillBuffer(L'!');
    Console console(mockBuffer);

    testing::internal::CaptureStdout();

    //When
    console.copyScreenToConsole();

    //Then
    std::string actual = testing::internal::GetCapturedStdout();
    std::wstring wideString(mockBuffer.buffer());
    std::string expected(wideString.begin(), wideString.end());
    ASSERT_EQ(actual, ""); // TODO - see below
}


//TODO - how to test the output - it doesn't go to cout

// what is the windows terminal application verifier

// The Windows Terminal Application Verifier is a tool that helps developers test their Windows applications for compatibility and stability.
// It is designed to help you detect issues that could prevent the applications from working correctly with other technologies,
// such as software drivers, services, or operating systems.
// The Windows Terminal Application Verifier can simulate user input, verify the applications’ behavior, and log errors if any are encountered.

// how do i use it?

// To use the Windows Terminal Application Verifier, you must first download and install it from the Microsoft website.
// Once you have installed the tool, you can use it to simulate user input and verify the behavior of your applications.
// The tool will log any errors that occur when the application is tested and will give you feedback as to what went wrong.
// After fixing any issues found, you can then rerun the tests to make sure the application works correctly.

// Can i incorporate it into googletest

// Yes, you can incorporate the Windows Terminal Application Verifier into Google Test.
// Google Test provides a framework that allows you to integrate external testing tools, such as the Windows Terminal Application Verifier, into your test suites.
// To use the Windows Terminal Application Verifier with Google Test, you will need to create a ‘custom listener’ and then register it with the Google Test library.
// This will allow the Windows Terminal Application Verifier to report results to the Google Test framework.