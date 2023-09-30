#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

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
}

void main_test_multimap()
{
    BEGIN_TEST;

    zen::multimap<zen::string, zen::string> mss = { {"A", "1"}, {"A", "2"}, {"A", "3"}, {"B", "4"}, {"B", "5"} };
    mss.insert({ "D", "6" });
    mss.insert({ "D", "7" });

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
}