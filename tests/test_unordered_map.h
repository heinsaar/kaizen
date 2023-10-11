#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

void test_unordered_map_of_strings()
{
    BEGIN_SUBTEST;

    zen::hash_map<zen::string, zen::string, zen::string_hash> v = { {"1", "1"} };
    ZEN_EXPECT(silent_print(v) == "[{\"1\", \"1\"}]");

    zen::hash_map<zen::string, int, zen::string_hash> x = { {"1", 1}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4} };
    x.insert({ "0", 0 });

    zen::hash_map<int, zen::string> y = { {1, "1"} };
    ZEN_EXPECT(silent_print(y) == "[{1, \"1\"}]");
    ZEN_EXPECT(x.contains("0"));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_unordered_map_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::hash_map<zen::string, int, zen::string_hash> v = { {"1", 1}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4} };

    std::unordered_map sv{ v };
    zen::unordered_map zv{ sv };

    zen::hash_map<zen::string, int, zen::string_hash> zc = [&]() { return sv; }();
    
    ZEN_EXPECT(zv == sv && sv == zc);
}

void test_unordered_multimap_of_strings()
{
    BEGIN_SUBTEST;
    zen::hash_multimap<zen::string, int, zen::string_hash> x = { {"1", 1}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4} };
    x.insert({ "0", 0 });
    x.insert({ "0", 0 });

    ZEN_EXPECT(x.contains("0") && x.size() == 7);
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());
}

void test_unordered_multimap_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::hash_multimap<zen::string, int, zen::string_hash> v = { {"1", 1}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4} };
    
    std::unordered_multimap sv{ v };
    zen::unordered_multimap zv{ sv };
    
    zen::hash_multimap<zen::string, int, zen::string_hash> zc = [&]() { return sv; }();
    
    ZEN_EXPECT(zv == sv && sv == zc);
}

void main_test_unordered_map()
{
    BEGIN_TEST;

    zen::unordered_map<int, zen::string> x = { {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"} };
    x.insert({0, "0"});

    ZEN_EXPECT(x.contains(0));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_map_zen_std_interchangeability();
    test_unordered_map_of_strings();
}

void main_test_unordered_multimap()
{
    BEGIN_TEST;

    zen::unordered_multimap<int, zen::string> x = { {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"} };
    x.insert({ 0, "0" });
    x.insert({ 0, "0" });

    ZEN_EXPECT(x.contains(0));
    ZEN_EXPECT(zen::is_empty(x) == x.is_empty());

    test_unordered_multimap_zen_std_interchangeability();
    test_unordered_multimap_of_strings();
}