#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_forward_list()
{
    BEGIN_TEST;

    const auto r = []{ return zen::random_int(); };

    zen::forward_list<int> x = { r(), r(), r(), r(), r()};
    x.push_front(777);

    zen::log("LIST:", x);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}