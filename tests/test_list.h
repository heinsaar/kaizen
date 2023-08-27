#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_list()
{
    zen::list<int> x;
    zen::populate_random(x);

    x.push_back(777);
    assert(x.contains(777));

    zen::print("TEST PASS:", __func__, " CONTENT", x);
}