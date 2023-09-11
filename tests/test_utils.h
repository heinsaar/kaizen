#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

// TODO: Remove these std includes below when "kaizen.h" includes them
#include <unordered_map>
#include <forward_list>
#include <set>
#include <map>

void test_utils_sum()
{
    zen::vector<int> v = { 1, 2, 3, 4, 5 };

    ZEN_EXPECT(zen::sum(v) == 15);
    ZEN_EXPECT(zen::sum(zen::vector<int>{}) == 0);

    // Test with std::list of floats
    std::list<float> float_list = { 1.5f, 2.5f, 3.5f };
    ZEN_EXPECT(zen::sum(float_list) == 7.5);

    // Test with std::array of doubles
    std::array<double, 3> double_array = { 1.1, 2.2, 3.3 };
    ZEN_EXPECT(zen::sum(double_array) == 6.6);

    // Test with std::forward_list
    std::forward_list<int> fwd_list = { 10, 20, 30 };
    ZEN_EXPECT(zen::sum(fwd_list) == 60);

    // Test with std::deque
    std::deque<int> int_deque = { 11, 22, 33 };
    ZEN_EXPECT(zen::sum(int_deque) == 66);

    // Test with std::set (no duplicates, ordered)
    std::set<int> int_set = { 5, 10, 15 };
    ZEN_EXPECT(zen::sum(int_set) == 30);

    // Test with std::map (should sum values, not keys)
    std::map<int, int> int_map = { {1, 2}, {3, 4}, {5, 6} };
    //zen::sum(int_map);  // should fail compilation with message: ZEN STATIC ASSERTION FAILED. "ELEMENT TYPE EXPECTED TO BE Addable, BUT IS NOT"

    // Test with std::unordered_map (should sum values, not keys)
    std::unordered_map<int, int> int_umap = { {1, 2}, {3, 4}, {5, 6} };
    //zen::sum(int_umap); // should fail compilation with message: ZEN STATIC ASSERTION FAILED. "ELEMENT TYPE EXPECTED TO BE Addable, BUT IS NOT"
}

void main_test_utils()
{
    BEGIN_TEST;
    zen::vector<int> v = {1, 2, 3, 4, 5};

    std::string s = zen::to_string(v);
    ZEN_EXPECT(s == "[1, 2, 3, 4, 5]");

    ZEN_EXPECT(zen::random_int() <= 10);

    test_utils_sum();
}