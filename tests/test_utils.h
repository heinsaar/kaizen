#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

void test_utils_sum()
{
    BEGIN_SUBTEST;

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

void test_utils_to_string()
{
    BEGIN_SUBTEST;

    std::vector<std::vector<std::vector<int>>> vvv     = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    std::vector<std::vector<int>>              vv      = { {1, 2}, {3, 4} };
    std::vector<std::vector<int>>              vve     = { {}, {}, {} };
    std::vector<std::list<int>>                vx      = { {1, 2}, {3, 4} };
    std::list<std::vector<int>>                xv      = { {1, 2}, {3, 4} };
    std::vector<int>                           vone    = { 1 };
    std::vector<int>                           v       = { 1, 2, 3 };
    std::vector<std::array<int, 2>>            va      = { {1, 2}, {3, 4} };
    std::vector<int>                           vmix    = { 1, 2, 3 };
    std::vector<int>                           vempty;

    ZEN_EXPECT(zen::to_string()                  == "");
    ZEN_EXPECT(zen::to_string(1, 2, 3)           == "1 2 3");
    ZEN_EXPECT(zen::to_string(42.24)             == "42.24");
    ZEN_EXPECT(zen::to_string("hello")           == "hello");
    ZEN_EXPECT(zen::to_string(v)                 == "[1, 2, 3]");
    ZEN_EXPECT(zen::to_string(vempty)            == "[]");
    ZEN_EXPECT(zen::to_string(1, 42.24, "hello") == "1 42.24 hello");
    ZEN_EXPECT(zen::to_string(vone)              == "[1]");
    ZEN_EXPECT(zen::to_string(vv)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(vve)               == "[[], [], []]");
    ZEN_EXPECT(zen::to_string(vx)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(xv)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(va)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(vvv)               == "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");
    ZEN_EXPECT(zen::to_string(vmix, "mixed", 42) == "[1, 2, 3] mixed 42");
}

void test_utils_print()
{
    BEGIN_SUBTEST;

    // Test with a number
    ZEN_EXPECT(silent_print(5) == "5");

    // Test with a string
    ZEN_EXPECT(silent_print("hello") == "hello");

    // Test with multiple arguments of mixed types
    ZEN_EXPECT(silent_print(5, "hello", 7.2) == "5 hello 7.2");

    // Test with a vector
    std::vector<int> v =          { 1, 2, 3 };
    ZEN_EXPECT(silent_print(v) == "[1, 2, 3]");

    // Test with nested containers
    std::vector<std::vector<int>> vv = { {1, 2}, {3, 4} };
    ZEN_EXPECT(silent_print(vv) ==     "[[1, 2], [3, 4]]");

    // Test with even more nested containers: vector, list, vector
    std::vector<std::list<std::vector<int>>> vxv = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(vxv) ==                "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with even more nested containers: list, vector, list
    std::list<std::vector<std::list<int>>> xvx = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(xvx) ==              "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with even more nested containers: list, vector, map
    std::list<std::vector<std::deque<int>>> xvd = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(xvd) ==               "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with mixed types
    ZEN_EXPECT(silent_print("Test", 1, 4.5) == "Test 1 4.5");

    // Test an empty print call
    ZEN_EXPECT(silent_print() == "");

    std::tuple<int, int, std::string, double> tup = { 1, 2,  "string in tuple",  3.9 };
    ZEN_EXPECT(silent_print(tup) ==                 "[1, 2, \"string in tuple\", 3.9]");

    std::tuple<int, int, std::pair<std::string, int>, double> tp = { 1, 2, { "string in tuple",  0}, 3.9 };
    ZEN_EXPECT(silent_print(tp) ==                                 "[1, 2, [\"string in tuple\", 0], 3.9]");

    std::tuple<int, int, std::tuple<int, std::string, int>, double> tt = { 1, 2, {0,  "string in tuple",  0}, 3.9 };
    ZEN_EXPECT(silent_print(tt)                                       == "[1, 2, [0, \"string in tuple\", 0], 3.9]");

    std::tuple<int, int, std::tuple<int, std::pair<std::string, int>, int>, double> ttp
                                  = { 1, 2, {0, { "string in tuple",  7}, 0}, 3.9 };
    ZEN_EXPECT(silent_print(ttp) == "[1, 2, [0, [\"string in tuple\", 7], 0], 3.9]");

    std::pair<int, std::pair<std::string, double>> pp = { 1, { "string in pair",  7.8}};
    ZEN_EXPECT(silent_print(pp) ==                      "[1, [\"string in pair\", 7.8]]");

    std::pair<int, std::pair<std::string, std::pair<double, std::string>>> ppp =
                                    { 1, { "string in pair",  {7.8,  "string in pair B" }}};
    ZEN_EXPECT(silent_print(ppp) == "[1, [\"string in pair\", [7.8, \"string in pair B\"]]]");

    std::tuple<int, int, std::tuple<int, std::pair<std::pair<std::string, std::string>, int>, int>, double> ttpp
                                   = { 1, 2, {0, {{ "string in tuple A",   "string in tuple B"},  7}, 0}, 3.9 };
    ZEN_EXPECT(silent_print(ttpp) == "[1, 2, [0, [[\"string in tuple A\", \"string in tuple B\"], 7], 0], 3.9]");
}

void test_utils_search_upward()
{
    BEGIN_SUBTEST;

    // Directory exists in the path
    ZEN_EXPECT(zen::search_upward("user", "/home/user/documents").value().filename() == "user");

    // Directory does not exist in the path
    ZEN_EXPECT(zen::search_upward("nonexistent", "/home/user/documents") == std::nullopt);

    // Root directory is reached
    ZEN_EXPECT(zen::search_upward("nonexistent", "/") == std::nullopt);

    // Searching for the root directory itself
    ZEN_EXPECT(zen::search_upward("/", "/").value().filename() == "");
    ZEN_EXPECT(zen::search_upward("",  "/").value().filename() == "");

    // Empty initial directory
    ZEN_EXPECT(zen::search_upward("nonexistent", "") == std::nullopt);
}

void test_utils_search_downward()
{
    BEGIN_SUBTEST;

    // Test case 1: When the directory exists within the depth
    auto r1 = zen::search_downward("CMakeCache.txt");
    ZEN_EXPECT(r1.has_value() && r1.value().filename() == "CMakeCache.txt");

    // Test case 2: When the directory does not exist
    auto r2 = zen::search_downward("nonexistent");
    ZEN_EXPECT(!r2.has_value() && r2 == std::nullopt);

    // Test case 3: When the file exists within the depth
    auto r3 = zen::search_downward("CMakeFiles");
    ZEN_EXPECT(r3.has_value() && r3.value().filename() == "CMakeFiles");

    // Test case 4: Limiting the depth
    auto r4 = zen::search_downward("file.txt", std::filesystem::path("/home/user"), 1);
    ZEN_EXPECT(r4 == std::nullopt);

    // Test case 5: When the initial directory is empty
    auto r5 = zen::search_downward("nonexistent", std::filesystem::path(""));
    ZEN_EXPECT(r5 == std::nullopt);
}

void main_test_utils()
{
    BEGIN_TEST;
    zen::vector<int> v = {1, 2, 3, 4, 5};

    std::string s = zen::to_string(v);
    ZEN_EXPECT(s == "[1, 2, 3, 4, 5]");

    ZEN_EXPECT(zen::random_int() <= 10);

    test_utils_search_downward();
    test_utils_search_upward();
    test_utils_to_string();
    test_utils_print();
    test_utils_sum();
}