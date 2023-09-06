#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_list()
{
    zen::log(zen::color::yellow("BEGIN TEST:"), __func__);

    zen::list<int> x;
    zen::populate_random(x);

    x.push_back(777);
    assert(x.contains(777));
}