#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_utils()
{
    zen::vector<int> v = {1, 2, 3, 4, 5};

    std::string s = zen::to_string(v);
    assert(s == "[1, 2, 3, 4, 5]");

    assert(zen::random_int() <= 10);

    zen::log(zen::color::green("TEST PASS:"), __func__);
}