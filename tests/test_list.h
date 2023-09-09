#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void main_test_list()
{
    zen::log("BEGIN TEST ------------------------------------------------", __func__);

    zen::list<int> x;
    zen::populate_random(x);
    x.push_back(777);

    zen::log("RANDOM LIST:", x);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}