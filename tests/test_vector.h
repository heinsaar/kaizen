#pragma once

#include "../build/kaizen.h" // test using generated header

void main_test_vector()
{
    BEGIN_TEST;
    zen::vector<int> v(10);
    zen::populate_random(v);
    v.push_back(777);

    zen::log("RANDOM VECTOR:", v);

    ZEN_EXPECT(v.contains(777));
    ZEN_EXPECT(zen::is_empty(v) == v.is_empty());
}