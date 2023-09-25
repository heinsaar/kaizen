#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_unordered_map_of_strings()
{
    BEGIN_SUBTEST;
    zen::hash_map<zen::string, int, zen::string_hash> x = { {"1", 1}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4} };
    x.insert({ "0", 0 });

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void main_test_unordered_map()
{
    BEGIN_TEST;

    zen::unordered_map<int, zen::string> x = { {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"} };
    x.insert({0, "0"});

    ZEN_EXPECT(x.contains(0));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_map_of_strings();
}