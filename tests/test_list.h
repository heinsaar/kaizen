#pragma once

#include "../build/kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_list()
{
    BEGIN_TEST;

    zen::list<int> x;
    zen::populate_random(x);
    x.push_back(777);

    //zen::log("RANDOM LIST:", x);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}