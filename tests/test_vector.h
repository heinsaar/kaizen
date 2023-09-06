#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_vector()
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);
    zen::vector<int> v(15);
    zen::populate_random(v);

    v.push_back(777);
    ZEN_EXPECT(v.contains(777));
}