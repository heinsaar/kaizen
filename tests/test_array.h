#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_array()
{
    zen::array<int, 5> a = { 1, 2, 3, 4, 5 };

    assert(a.contains(5));

    zen::log(zen::color::green("TEST PASS:"), __func__, " CONTENT", a);
}