#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_list()
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);

    zen::list<int> x;
    zen::populate_random(x);

    x.push_back(777);
    ZEN_EXPECT(x.contains(777));
}