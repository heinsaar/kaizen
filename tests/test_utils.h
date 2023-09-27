#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

// TODO: Remove these std includes below when "kaizen.h" includes them
#include <unordered_map>
#include <forward_list>
#include <set>
#include <map>

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
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect the output

    // Testing zen::print() is a special case since we're testing the same function
    // that's also used for test output log. Therefore, in order not to pollute the
    // test output log, we save the standard cout buffer into old_buf at the top of
    // this function, and restore to it after each test so that each test ends with
    // a restoration of the system to printing into the standard output.
    // 
    // The tests in between juggle around in a way so that ZEN_EXPECT (which uses zen::log(),
    // which in turn uses zen::print()) behaves as expected instead of outputting into the
    // intermediate stream used for testing the zen::print(). Tests follow this pattern:
    // 
    // 1. Reset a local std::stringstream object state to an empty string
    // 1. Redirect cout into the local std::stringstream object
    // 1. Call zen::print(), which will output into the std::stringstream object
    // 2. Temporarily redirect cout back to the standard output for the subsequent ZEN_EXPECT()
    // 3. Use ZEN_EXPECT() with the standard output

    // Test with a number
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    zen::print(5);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "5");

    // Test with a string
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    zen::print("hello");
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "hello");

    // Test with multiple arguments of mixed types
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    zen::print(5, "hello", 7.2);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "5 hello 7.2");

    // Test with a vector
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    std::vector<int> v = { 1, 2, 3 };
    zen::print(v);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "[1, 2, 3]");

    // Test with nested containers
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    std::vector<std::vector<int>> vv = { {1, 2}, {3, 4} };
    zen::print(vv);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "[[1, 2], [3, 4]]");

    // Test with even more nested containers: vector, list, vector
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    std::vector<std::list<std::vector<int>>> vxv = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    zen::print(vxv);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with even more nested containers: list, vector, list
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    std::list<std::vector<std::list<int>>> xvx = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    zen::print(xvx);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with even more nested containers: list, vector, map
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    std::list<std::vector<std::deque<int>>> xvd = { {{1, 2}, {3, 4}}, {{5, 6}, {7, 8}} };
    zen::print(xvd);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "[[[1, 2], [3, 4]], [[5, 6], [7, 8]]]");

    // Test with mixed types
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    zen::print("Test", 1, 4.5);
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "Test 1 4.5");

    // Test an empty print call
    ss.str("");
    std::cout.rdbuf(ss.rdbuf()); // redirect to a local stream
    zen::print();
    std::cout.rdbuf(old_buf);    // back to standard output
    ZEN_EXPECT(ss.str() == "");
}

void test_utils_search_upward()
{
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