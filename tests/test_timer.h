#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_timer()
{
    BEGIN_TEST;

    zen::timer timer;

    for (int i : zen::in(100)) {
        // Trim and deflate a string
        zen::string z = "   Trim   me  ";
        std::string s = z.trim(); // from leading & trailing empty spaces

        // C assert instead of ZEN_EXPECT so as not to
        // confuse the different test case counter
        assert(!::isspace(s.front()));
        assert(!::isspace(s.back()));
    }

    timer.stop();
}