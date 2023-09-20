#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_vector_of_strings()
{
    BEGIN_SUBTEST;
    zen::vector<zen::string> v = { "1", "2", "3", "4" };
    v.push_back("0");

    //zen::log(typeid(v).name(), v);

    ZEN_EXPECT(v.contains("0"));
    ZEN_EXPECT(zen::is_empty(v) == v.is_empty());
}

void main_test_vector()
{
    BEGIN_TEST;
    zen::vector<int> v(10);
    zen::generate_random(v);
    v.push_back(777);

    //zen::log("RANDOM VECTOR:", v);

    ZEN_EXPECT(v.contains(777));
    ZEN_EXPECT(zen::is_empty(v) == v.is_empty());

    test_vector_of_strings();
}