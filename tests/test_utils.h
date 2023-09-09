#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void main_test_utils()
{
    BEGIN_TEST;
    zen::vector<int> v = {1, 2, 3, 4, 5};

    std::string s = zen::to_string(v);
    ZEN_EXPECT(s == "[1, 2, 3, 4, 5]");

    ZEN_EXPECT(zen::random_int() <= 10);
}