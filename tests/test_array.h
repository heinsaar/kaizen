#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_array()
{
    BEGIN_TEST;

    zen::array<int, 5> a = { 1, 2, 3, 4, 5 };

    //zen::log("ARRAY:", a);

    ZEN_EXPECT( a.contains(5));
    ZEN_EXPECT(!a.contains(7));
    ZEN_EXPECT(zen::is_empty(a) == a.is_empty());
}