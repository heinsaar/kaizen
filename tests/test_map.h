#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

void test_map_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::dictionary v = { {"A", "1"}, {"B", "2"}, {"C", "3"} };

    std::map sv{ v };
    zen::map zv{ sv };

    zen::dictionary zc = [&]() { return sv; }();

    ZEN_EXPECT(zv == sv && sv == zc);
}

void test_multimap_zen_std_interchangeability()
{
    BEGIN_SUBTEST;
    zen::multimap<zen::string, zen::string> v = { {"A", "1"}, {"A", "2"}, {"A", "3"}, {"B", "4"}, {"B", "5"} };

    std::multimap sv{ v };
    zen::multimap zv{ sv };

    zen::multimap zc = [&]() { return sv; }();

    ZEN_EXPECT(zv == sv && sv == zc);
}

void main_test_map()
{
    BEGIN_TEST;

    zen::dictionary m = { {"A", "1"}, {"B", "2"}, {"C", "3"} };
    m.insert({ "D", "4" });

    ZEN_EXPECT( m.contains({ "A" }));
    ZEN_EXPECT(!m.contains({ "X" }));
    ZEN_EXPECT( m["A"].contains("1"));
    ZEN_EXPECT(!m["A"].contains("x"));
    
    ZEN_EXPECT(zen::is_empty(m) == m.is_empty());

    test_map_zen_std_interchangeability();
}

void main_test_multimap()
{
    BEGIN_TEST;

    zen::multimap<zen::string, zen::string> mss = { {"A", "1"}, {"A", "2"}, {"A", "3"}, {"B", "4"}, {"B", "5"} };
    mss.insert({ "D", "6" });
    mss.insert({ "D", "7" });

    zen::multimap<std::pair<zen::string, zen::string>, zen::string> mps = { {{"A", "A"}, "1"}, {{"B", "B"}, "2"} };

    ZEN_EXPECT(silent_print(mss) == "[[A, 1], [A, 2], [A, 3], [B, 4], [B, 5], [D, 6], [D, 7]]");
    ZEN_EXPECT(silent_print(mps) == "[[[A, A], 1], [[B, B], 2]]");

    ZEN_EXPECT(!mss.contains({ "X" }));
    ZEN_EXPECT(
        mss.count("A") == 3 &&
        mss.count("D") == 2
    );
    ZEN_EXPECT(
        mss["A"][0] == "1" &&
        mss["A"][1] == "2" &&
        mss["A"].size() == 3
    );
    ZEN_EXPECT(mss["D"].size() == 2);
    
    ZEN_EXPECT(zen::is_empty(mss) == mss.is_empty());

    test_multimap_zen_std_interchangeability();
}