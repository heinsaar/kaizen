#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_unordered_set_of_strings()
{
    BEGIN_SUBTEST;
    zen::unordered_set<zen::string, zen::string_hash> x = { "1", "2", "3", "4" };
    x.insert("0");
    
    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void main_test_unordered_set()
{
    BEGIN_TEST;

    zen::unordered_set<int> x = { 1, 2, 3, 4 };
    x.insert(777);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_set_of_strings();
}