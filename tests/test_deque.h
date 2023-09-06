#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_deque()
{
    zen::log(zen::color::yellow("BEGIN TEST------------------------------------------------"), __func__);

    zen::deque<int> q;
    zen::populate_random(q);

    q.push_back(777);
    ZEN_EXPECT(q.contains(777));
}