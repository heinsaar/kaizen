#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_array()
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);

    zen::array<int, 5> a = { 1, 2, 3, 4, 5 };

    ZEN_EXPECT(a.contains(5));
}