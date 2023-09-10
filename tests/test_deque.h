#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_deque()
{
    BEGIN_TEST;

    zen::deque<int> q;
    zen::populate_random(q);
    q.push_back(777);

    //zen::log("RANDOM DEQUE:", q);

    ZEN_EXPECT(q.contains(777));
    ZEN_EXPECT(zen::is_empty(q) == q.is_empty());
}