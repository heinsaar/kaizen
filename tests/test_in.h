#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_in()
{
    BEGIN_TEST;

    std::string s1 = "(5): ";
    for (int i : zen::in(5))
        s1 += std::to_string(i) + " ";

    std::string s2 = "[1, 10): ";
    for (int i : zen::in(1, 10))
        s2 += std::to_string(i) + " ";

    std::string s3 = "[1, 10, 2): ";
    for (int i : zen::in(1, 10, 2))
        s3 += std::to_string(i) + " ";

    std::string s4 = "[10, 1, -1): ";
    for (int i : zen::in(10, 1, -1))
        s4 += std::to_string(i) + " ";

    std::string s5 = "[1, 10, -1): ";
    for (int i : zen::in(1, 10, -1))
        s5 += std::to_string(i) + " ";

    std::string s6 = "[-10, 10, 1): ";
    for (int i : zen::in(-10, 10, 1))
        s6 += std::to_string(i) + " ";

    ZEN_EXPECT(s1 == "(5): 0 1 2 3 4 ");
    ZEN_EXPECT(s2 == "[1, 10): 1 2 3 4 5 6 7 8 9 ");
    ZEN_EXPECT(s3 == "[1, 10, 2): 1 3 5 7 9 ");
    ZEN_EXPECT(s4 == "[10, 1, -1): 10 9 8 7 6 5 4 3 2 ");
    ZEN_EXPECT(s5 == "[1, 10, -1): ");
    ZEN_EXPECT(s6 == "[-10, 10, 1): -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 ");
}