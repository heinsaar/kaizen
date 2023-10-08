#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_unordered_set_of_strings()
{
    BEGIN_SUBTEST;
    zen::hash_set<zen::string, zen::string_hash> x = { "1", "2", "3", "4" };
    x.insert("0");

    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_unordered_set_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::hash_set<zen::string, zen::string_hash> v = { "1", "2", "3", "4" };
    
    std::unordered_set sv{ v };
    zen::unordered_set zv{ sv };

    zen::hash_set<zen::string, zen::string_hash> zc = [&]() { return sv; }();
    
    ZEN_EXPECT(zv == sv && sv == zc);
}

void test_unordered_multiset_of_strings()
{
    BEGIN_SUBTEST;
    zen::hash_multiset<zen::string, zen::string_hash> x = { "1", "1", "2", "2" };
    x.insert("0");
    x.insert("0");

    ZEN_EXPECT(x.count("0") == 2 && x.size() == 6);
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_unordered_multiset_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::hash_multiset<zen::string, zen::string_hash> v = { "1", "1", "2", "2" };

    std::unordered_multiset sv{ v };
    zen::unordered_multiset zv{ sv };

    zen::hash_multiset<zen::string, zen::string_hash> zc = [&]() { return sv; }();

    ZEN_EXPECT(zv == sv && sv == zc);
}

void main_test_unordered_set()
{
    BEGIN_TEST;

    zen::unordered_set<int> x = { 1, 2, 3, 4 };
    x.insert(777);

    ZEN_EXPECT(x.contains(777) && x.size() == 5);
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_set_zen_std_interchangeability();
    test_unordered_set_of_strings();
}

void main_test_unordered_multiset()
{
    BEGIN_TEST;

    zen::unordered_multiset<int> x = { 1, 1, 2, 2, 3, 3 };
    x.insert(888);
    x.insert(888);

    ZEN_EXPECT(x.contains(888) && x.size() == 8);
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_multiset_zen_std_interchangeability();
    test_unordered_multiset_of_strings();
}