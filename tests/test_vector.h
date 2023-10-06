#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_vector_of_strings()
{
    BEGIN_SUBTEST;
    zen::vector<zen::string> v = { "1", "2", "3", "4" };
    v.push_back("0");

    zen::strings zs = v;

    ZEN_EXPECT(v.contains("0") == zs.contains("0"));
    ZEN_EXPECT(zen::is_empty(v) == v.is_empty());
}

void test_vector_zen_std_interchangability()
{
    BEGIN_SUBTEST;
    zen::vector<int> v = { 1, 2, 3 };

    std::vector sv{ v };
    zen::vector zv{ sv };

    zen::vector<int> zc = [&]() { return sv; }();

    ZEN_EXPECT(v.contains(1) && zv.contains(2));
    ZEN_EXPECT(zc == sv && sv == zv);
}

void main_test_vector()
{
    BEGIN_TEST;
    zen::vector<int> v;
    zen::generate_random(v);
    v.push_back(777);

    ZEN_EXPECT(v.contains(777));
    ZEN_EXPECT(zen::is_empty(v) == v.is_empty());

    test_vector_zen_std_interchangability();
    test_vector_of_strings();
}