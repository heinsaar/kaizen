// MIT License
// 
// Copyright (c) 2023 Leo Heinsaar
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <string_view>
#include <iostream>
#include <sstream>
#include <random>
#include <atomic>
#include <ctime>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// USEFUL MISC

std::atomic<int> TEST_CASE_PASS_COUNT = 0; // atomic in case tests are ever parallelized
std::atomic<int> TEST_CASE_FAIL_COUNT = 0; // atomic in case tests are ever parallelized

#define ZEN_STATIC_ASSERT(X, M) static_assert(X, "ZEN: " M)

// ZEN_EXPECT checks its condition parameter and spits out the condition statement if it fails.
// The do { } while (0) construct ensures that the macro behaves as a single statement.
// This allows it to be used safely in contexts like if-else statements without braces,
// preventing syntax errors or unexpected behavior due to dangling elses.
#define ZEN_EXPECT(cond) \
    do { \
        if (cond) { \
            zen::log(zen::color::green("CASE PASS:"), #cond); \
            ++zen::TEST_CASE_PASS_COUNT; \
        } \
        if (!(cond)) { \
            zen::log(zen::color::red("CASE FAIL:"), __func__, "EXPECTED:", #cond); \
            ++zen::TEST_CASE_FAIL_COUNT; \
        } \
    } while (0)

inline auto quote(const std::string_view s) { return '\"' + std::string(s) + '\"'; }

inline auto timestamp() {
    std::time_t result  = std::time(nullptr);
    std::string timestr = std::asctime(std::localtime(&result));
    return timestr.substr(0, timestr.length() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////// MAIN UTILITIES

template<class T = int>
T random_int(const T min = 0, const T max = 10) {
    // Reasons why the std::random_device and the std::mt19937 are 'static' below:
    // ---------------------------------------------------------------------------------------------------------------
    // 1. Initialization Efficiency:
    // Random devices and generators often involve some computational cost due to entropy gathering, seeding, generator
    // initialization and good old algorithmic complexity. By declaring them as static, they are initialized only once,
    // the first time the function is called. Subsequent calls to to this function reuse the existing instances, avoiding the overhead.
    // ---------------------------------------------------------------------------------------------------------------
    // 2. State Preservation:
    // Random number generators like std::mt19937 maintain an internal state that evolves as numbers are generated.
    // This state determines the sequence of random numbers produced. By making the std::mt19937 object static,
    // the state is preserved across calls to this function, ensuring a proper random sequence. If the std::mt19937
    // object were reinitialized on every call, it might lead to repeated or patterned sequences, undermining the randomness.
    // ---------------------------------------------------------------------------------------------------------------
    // 3. Thread Safety Considerations:
    // Declaring these variables as static within a function means they are shared across all calls to that function
    // within the program, regardless of where it's called from. This could potentially raise thread-safety issues if the
    // function is called simultaneously from multiple threads. However, in most common usage scenarios where thread
    // safety is not a concern, using static variables for this purpose is fine.
    // ---------------------------------------------------------------------------------------------------------------
    // 4. Resource Management
    // Since the std::random_device and the std::mt19937 object are static, they are not destroyed when the function returns,
    // but rather when the program ends. This ensures that the same random device and generator instances are reused
    // throughout the lifetime of the program, optimizing resource management.
    // ---------------------------------------------------------------------------------------------------------------
    // 5. Avoiding Repetition
    // If we didn't make these objects static, and the random number generator was reseeded with the same or similar
    // seeds (which might happen if the function is called in quick succession), you might get the same or similar random
    // numbers in different calls. Making these static ensures a more varied and truly random sequence.
    // ---------------------------------------------------------------------------------------------------------------
    // The 'static' below is for reasons outlined above.
    static std::random_device        rd;
    static std::mt19937              gen(rd());
    std::uniform_int_distribution<T> dis(min, max);
    return dis(gen);
}

template<class Iterable>
void populate_random(Iterable& c, int size = 10)
{
    ZEN_STATIC_ASSERT(zen::is_iterable_v<Iterable>, "TEMPLATE PARAMETER C EXPECTED TO BE ITERABLE, BUT IS NOT");

    if (!std::size(c))
        c.resize(size);

    std::generate(std::begin(c), std::end(c), [&]() { return random_int(10, 99); });
}

template<class Iterable>
bool is_empty(const Iterable& c)
{
    ZEN_STATIC_ASSERT(zen::is_iterable_v<Iterable>, "TEMPLATE PARAMETER C EXPECTED TO BE ITERABLE, BUT IS NOT");
    return c.empty();
}

///////////////////////////////////////////////////////////////////////////////////////////// COLORS

namespace color {
    struct color_string {
        color_string(const std::string_view s, int c) : text(s), code(c) {}
        const std::string text;
        const int /*col*/ code;

        friend std::ostream& operator<<(std::ostream& os, const color_string& cw) {
            os << "\033[" << cw.code << "m" << cw.text << "\033[0m";
            return os;
        }
    };

    color_string nocolor(const std::string_view s) { return color_string(s,  0); }
    color_string red    (const std::string_view s) { return color_string(s, 31); }
    color_string blue   (const std::string_view s) { return color_string(s, 34); }
    color_string green  (const std::string_view s) { return color_string(s, 32); }
    color_string black  (const std::string_view s) { return color_string(s, 30); }
    color_string yellow (const std::string_view s) { return color_string(s, 33); }
    color_string magenta(const std::string_view s) { return color_string(s, 35); }
    color_string cyan   (const std::string_view s) { return color_string(s, 36); }
    color_string white  (const std::string_view s) { return color_string(s, 37); }
}

///////////////////////////////////////////////////////////////////////////////////////////// LPS (Log, Print, String)
// 
// Printing and logging in Kaizen follows the LPS principle of textual visualization.
// The LPS principle: from string to print to log. This means that:
// 1. to_string() - is the transformation of an object into a string
// 2. print()     - uses to_string() to output the object (as a string)
// 3. log()       - uses print() and adds any formatting, new lines at the end, etc.

// ------------------------------------------------------------------------------------------ stringify

// Overload for containers like vector, list, etc.
template<class T>
zen::string to_string(const T& x) {
    std::stringstream ss;
    if constexpr (is_string_like<T>()) { // so that zen::pring("abc") prints "abc" and not [a, b, c]
       return x;                         // as a result of considering strings as iterable below
    }
    if constexpr (is_iterable_v<T>) {
        ss << "[";
        auto it = std::begin(x);
        if (it != std::end(x)) {
            ss << *it++;
        }
        for (; it != std::end(x); ++it) {
            ss << ", " << *it;
        }
        ss << "]";
    } else { // not iterable, single item
        ss << x;
    }
    return ss.str();
}

// Recursive variadic template to handle multiple arguments
template<class T, class... Args>
inline zen::string to_string(const T& x, const Args&... args) {
    return to_string(x) + " " + to_string(args...);
}
// Base case for the recursive calls
inline zen::string to_string() { return ""; }

// ------------------------------------------------------------------------------------------ print

// Function to handle individual item printing
template <class T>
void print(const T& x)
{
    std::cout << to_string(x);
}

// Generic, almost Python-like print(). Works like this:
// print("Hello", "World", vec, 42); // Output: Hello World [1, 2, 3] 42
// print("Hello", "World", 24, vec); // Output: Hello World 24 [1, 2, 3]
// print("Hello", vec, 42, "World"); // Output: Hello [1, 2, 3] 42 World
template <class T, class... Args>
void print(T x, Args... args) {
    print(x);
    if constexpr (sizeof...(args) != 0) {
        std::cout << " ";
    }
    print(args...);
}
// Base case for the recursive calls
inline void print() {}

// ------------------------------------------------------------------------------------------ log

// Handles logging a single item
template <class T>
void log(const T& x)
{
    print(x, '\n');
}

// Generic, almost Python-like log(). Works similar to the print() function but adds std::endl
template <class T, class... Args>
void log(T x, Args... args) {
    print(x, args...);
    std::cout << std::endl;
}
// Base case for the recursive calls
inline void log() {}

} // namespace zen