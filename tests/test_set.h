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

void main_test_multiset()
{
    BEGIN_SUBTEST;
    zen::multiset<zen::string> x = { "1", "1", "3", "4", "4"};
    x.insert("0");

    ZEN_EXPECT(silent_print(x) == "[0, 1, 1, 3, 4, 4]");

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void main_test_set()
{
    BEGIN_TEST;

    zen::set<int> q = { 1, 2, 3, 4 };
    q.insert(777);

    ZEN_EXPECT(silent_print(q) == "[1, 2, 3, 4, 777]");

    ZEN_EXPECT(q.contains(777));
    ZEN_EXPECT(zen::is_empty(q) == q.is_empty());

    test_set_of_strings();
}