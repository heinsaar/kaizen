#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_utils()
{
    zen::log(zen::color::yellow("BEGIN TEST:"), __func__);
    zen::vector<int> v = {1, 2, 3, 4, 5};

    std::string s = zen::to_string(v);
    assert(s == "[1, 2, 3, 4, 5]");

    assert(zen::random_int() <= 10);
}