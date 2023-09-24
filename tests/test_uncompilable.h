#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_uncompilable()
{
    // To "run" this test, uncomment "test_uncompilable.h" in test_kaizen.h

    // The following should not compile since their
    // dynamic allocation has been disabled
    //auto* _1 = new zen::forward_list<int>;
    //auto* _2 = new zen::array<int, 4>;
    //auto* _4 = new zen::map<int, int>;
    //auto* _3 = new zen::vector<int>;
    //auto* _5 = new zen::deque<int>;
    //auto* _6 = new zen::list<int>;
    //auto* _7 = new zen::set<int>;
    //auto* _8 = new zen::string;
}