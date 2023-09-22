#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_map_of_strings()
{
    BEGIN_SUBTEST;

    zen::keyval m = { {"A", "1"}, {"B", "2"}, {"C", "3"} };
    m.insert({ "D", "4" });

    ZEN_EXPECT( m.contains({ "A" }));
    ZEN_EXPECT(!m.contains({ "X" }));

    ZEN_EXPECT(zen::is_empty(m) == m.is_empty());
}

void main_test_map()
{
    BEGIN_TEST;

    zen::dictionary m = { {"A", "1"}, {"B", "2"}, {"C", "3"} };
    m.insert({ "D", "4" });

    ZEN_EXPECT( m.contains({ "A" }));
    ZEN_EXPECT(!m.contains({ "X" }));
    
    ZEN_EXPECT(zen::is_empty(m) == m.is_empty());

    test_map_of_strings();
}