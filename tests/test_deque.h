#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_deque()
{
    zen::deque<int> q;
    zen::populate_random(q);

    q.push_back(777);
    assert(q.contains(777));

    zen::print("TEST PASS:", __func__, " CONTENT", q);
}