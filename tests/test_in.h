#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_in()
{
    zen::log("BEGIN TEST ------------------------------------------------", __func__);

    std::string s = "(5): ";
    for (int i : zen::in(5))
        s += std::to_string(i) + " ";
    ZEN_EXPECT(s == "(5): 0 1 2 3 4 ");

    s = "[1, 10): ";
    for (int i : zen::in(1, 10))
        s += std::to_string(i) + " ";
    ZEN_EXPECT(s == "[1, 10): 1 2 3 4 5 6 7 8 9 ");

    s = "[1, 10, 2): ";
    for (int i : zen::in(1, 10, 2))
        s += std::to_string(i) + " ";
    ZEN_EXPECT(s == "[1, 10, 2): 1 3 5 7 9 ");

    s = "[10, 1, -1): ";
    for (int i : zen::in(10, 1, -1))
        s += std::to_string(i) + " ";
    zen::log(s);
    ZEN_EXPECT(s == "[10, 1, -1): 10 9 8 7 6 5 4 3 2 ");

    s = "[1, 10, -1): ";
    for (int i : zen::in(1, 10, -1))
        s += std::to_string(i) + " ";
    ZEN_EXPECT(s == "[1, 10, -1): ");

    s = "[-10, 10, 1): ";
    for (int i : zen::in(-10, 10, 1))
        s += std::to_string(i) + " ";
    ZEN_EXPECT(s == "[-10, 10, 1): -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9 ");
}