#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

void test_forward_list_of_strings()
{
    BEGIN_SUBTEST;
    zen::forward_list<zen::string> x = { "1", "2", "3", "4" };
    x.push_front("0");

    ZEN_EXPECT(silent_print(x) == "[\"0\", \"1\", \"2\", \"3\", \"4\"]");
    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_forward_list_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::forward_list<int> v = { 1, 2, 3 };

    std::forward_list sv{ v };
    zen::forward_list zv{ sv };

    zen::forward_list<int> zc = [&]() { return sv; }();

    ZEN_EXPECT(v.contains(1) && zv.contains(2));
    ZEN_EXPECT(zc == sv && sv == zv);
}

void main_test_forward_list()
{
    BEGIN_TEST;

    const auto r = []{ return zen::random_int(); };

    zen::forward_list<int> x = { r(), r(), r(), r(), r()};
    x.push_front(777);

    ZEN_EXPECT(x.contains(777));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_forward_list_zen_std_interchangeability();
    test_forward_list_of_strings();
}