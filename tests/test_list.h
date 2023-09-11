#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_list_of_strings()
{
    BEGIN_SUBTEST;
    zen::list<zen::string> x = { "1", "2", "3", "4" };
    x.push_back("0");

    //zen::log(typeid(x).name(), x);

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void main_test_list()
{
    BEGIN_TEST;

    zen::list<int> x;
    zen::populate_random(x);
    x.push_back(777);

    //zen::log("RANDOM LIST:", x);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_list_of_strings();
}