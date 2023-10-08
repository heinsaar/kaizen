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

void test_utils_count()
{
    BEGIN_SUBTEST;
    
    zen::vector<int> x1 = { 1, 1, 3, 4, 5 };
    std::list<int>   x2 = { 1, 2, 2, 4, 5 };
    std::deque<int>  x3 = { 1, 1, 2, 3 };
    std::set<int>    x4 = { 1, 1, 2, 3 }; // sets do not allow duplicates

    ZEN_EXPECT(zen::count(zen::ints{}, 1) == 0);
    ZEN_EXPECT(zen::count(x1,          1) == 2);
    ZEN_EXPECT(zen::count(x2,          2) == 2);
    ZEN_EXPECT(zen::count(x3,          1) == 2);
    ZEN_EXPECT(zen::count(x4,          1) == 1);
}

void test_utils_count_if()
{
    BEGIN_SUBTEST;

    zen::vector<int> x1 = { 1, 2, 3, 4, 5 };
    std::list<int>   x2 = { 1, 2, 3, 4, 5 };
    std::deque<int>  x3 = { 1, 2, 3, 4, 5 };
    std::set<int>    x4 = { 1, 2, 3, 4, 5 };

    ZEN_EXPECT(zen::count_if(zen::ints{}, [](int i) { return i > 0;      }) == 0);
    ZEN_EXPECT(zen::count_if(x1,          [](int i) { return i > 2;      }) == 3);
    ZEN_EXPECT(zen::count_if(x2,          [](int i) { return i % 2 == 0; }) == 2);
    ZEN_EXPECT(zen::count_if(x3,          [](int i) { return i < 3;      }) == 2);
    ZEN_EXPECT(zen::count_if(x4,          [](int i) { return i == 3;     }) == 1);
}

void test_utils_to_string()
{
    BEGIN_SUBTEST;

    std::vector<std::vector<std::vector<int>>> v1 = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    std::vector<std::vector<int>>              v2 = { {1, 2}, {3, 4} };
    std::vector<std::vector<int>>              v3 = { {}, {}, {} };
    std::vector<std::list<int>>                v4 = { {1, 2}, {3, 4} };
    std::list<std::vector<int>>                v5 = { {1, 2}, {3, 4} };
    std::vector<int>                           v6 = { 1 };
    std::vector<int>                           v7 = { 1, 2, 3 };
    std::vector<std::array<int, 2>>            v8 = { {1, 2}, {3, 4} };
    std::vector<int>                           v9;

    ZEN_EXPECT(zen::to_string()                  == "");
    ZEN_EXPECT(zen::to_string(1, 2, 3)           == "1 2 3");
    ZEN_EXPECT(zen::to_string(42.24)             == "42.24");
    ZEN_EXPECT(zen::to_string("hello")           == "hello");
    ZEN_EXPECT(zen::to_string(v7)                == "[1, 2, 3]");
    ZEN_EXPECT(zen::to_string(v9)                == "[]");
    ZEN_EXPECT(zen::to_string(1, 42.24, "hello") == "1 42.24 hello");
    ZEN_EXPECT(zen::to_string(v6)                == "[1]");
    ZEN_EXPECT(zen::to_string(v2)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(v3)                == "[[], [], []]");
    ZEN_EXPECT(zen::to_string(v4)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(v5)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(v8)                == "[[1, 2], [3, 4]]");
    ZEN_EXPECT(zen::to_string(v1)                == "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");
    ZEN_EXPECT(zen::to_string(v7, "mixed", 42)   == "[1, 2, 3] mixed 42");
}

void test_utils_print()
{
    BEGIN_SUBTEST;

    // Number
    ZEN_EXPECT(silent_print(5) == "5");

    // String
    ZEN_EXPECT(silent_print("hello") == "hello");

    // Multiple arguments of mixed types
    ZEN_EXPECT(silent_print(5, "hello", 7.2) == "5 hello 7.2");

    // Vector
    std::vector<int> v =          { 1, 2, 3 };
    ZEN_EXPECT(silent_print(v) == "[1, 2, 3]");

    // Nested containers
    std::vector<std::vector<int>> vv = { {1, 2}, {3, 4} };
    ZEN_EXPECT(silent_print(vv) ==     "[[1, 2], [3, 4]]");

    // Even more nested containers: vector, list, vector
    std::vector<std::list<std::vector<int>>> vxv = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(vxv) ==                "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Even more nested containers: list, vector, list
    std::list<std::vector<std::list<int>>> xvx = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(xvx) ==              "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Even more nested containers: list, vector, map
    std::list<std::vector<std::deque<int>>> xvd = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    ZEN_EXPECT(silent_print(xvd) ==               "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Mixed types
    ZEN_EXPECT(silent_print("Test", 1, 4.5) == "Test 1 4.5");

    // Empty print call
    ZEN_EXPECT(silent_print() == "");

    // Strings nested in pairs and tuples nested in each other in various ways

    std::tuple<int, int, std::string, double> tup = { 1, 2,  "tuplestr",  3.9 };
    ZEN_EXPECT(silent_print(tup) ==                 "[1, 2, \"tuplestr\", 3.9]");

    std::tuple<int, int, std::pair<std::string, int>, double> tp = { 1, 2, { "tuplestr",  0}, 3.9 };
    ZEN_EXPECT(silent_print(tp) ==                                 "[1, 2, [\"tuplestr\", 0], 3.9]");

    std::tuple<int, int, std::tuple<int, std::string, int>, double> tt = { 1, 2, {0,  "tuplestr",  0}, 3.9 };
    ZEN_EXPECT(silent_print(tt)                                       == "[1, 2, [0, \"tuplestr\", 0], 3.9]");

    std::tuple<int, int, std::tuple<int, std::pair<std::string, int>, int>, double>
                            ttp   = { 1, 2, {0, { "tuplestr",  7}, 0}, 3.9 };
    ZEN_EXPECT(silent_print(ttp) == "[1, 2, [0, [\"tuplestr\", 7], 0], 3.9]");

    std::pair<int, std::pair<std::string, double>> pp = { 1, { "pairstr",  7.8}};
    ZEN_EXPECT(silent_print(pp) ==                      "[1, [\"pairstr\", 7.8]]");

    std::pair<int, std::pair<std::string, std::pair<double, std::string>>>
                            ppp =   { 1, { "pairstr",  {7.8,  "pairstr B" }}};
    ZEN_EXPECT(silent_print(ppp) == "[1, [\"pairstr\", [7.8, \"pairstr B\"]]]");

    std::tuple<int, int, std::tuple<int, std::pair<std::pair<std::string, std::string>, int>, int>, double>
                            ttpp   = { 1, 2, {0, {{ "tuplestr A",   "tuplestr B"},  7}, 0}, 3.9 };
    ZEN_EXPECT(silent_print(ttpp) == "[1, 2, [0, [[\"tuplestr A\", \"tuplestr B\"], 7], 0], 3.9]");
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

    ZEN_EXPECT_NOTHROW([]{}());

    test_utils_search_downward();
    test_utils_search_upward();
    test_utils_to_string();
    test_utils_count_if();
    test_utils_print();
    test_utils_count();
    test_utils_sum();
}