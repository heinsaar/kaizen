#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_vector()
{
    zen::vector<int> v(15);
    zen::populate_random(v);

    v.push_back(777);
    assert(v.contains(777));

    zen::log(zen::color::green("TEST PASS:"), __func__, " CONTENT", v);
}