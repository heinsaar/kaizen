#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

void test_set_of_strings()
{
    BEGIN_SUBTEST;
    zen::set<zen::string> x = { "1", "2", "3", "4" };
    x.insert("0");

    ZEN_EXPECT(silent_print(x) == "[0, 1, 2, 3, 4]");

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_set_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::set<zen::string> v = { "1", "2", "3", "4" };

    std::set sv{ v };
    zen::set zv{ sv };

    zen::set<zen::string> zc = [&]() { return sv; }();

    ZEN_EXPECT(zv == sv && sv == zc);
}

void test_multiset_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::multiset<zen::string> v = { "1", "1", "2", "2" };

    std::multiset sv{ v };
    zen::multiset zv{ sv };

    zen::multiset<zen::string> zc = [&]() { return sv; }();

    ZEN_EXPECT(zv == sv && sv == zc);
}

void main_test_multiset()
{
    BEGIN_SUBTEST;
    zen::multiset<zen::string> x = { "1", "1", "3", "4", "4"};
    x.insert("0");

    ZEN_EXPECT(silent_print(x) == "[0, 1, 1, 3, 4, 4]");

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_multiset_zen_std_interchangeability();
}

void main_test_set()
{
    BEGIN_TEST;

    zen::set<int> q = { 1, 2, 3, 4 };
    q.insert(777);

    ZEN_EXPECT(silent_print(q) == "[1, 2, 3, 4, 777]");

    ZEN_EXPECT(q.contains(777));
    ZEN_EXPECT(zen::is_empty(q) == q.is_empty());

    test_set_zen_std_interchangeability();
    test_set_of_strings();
}