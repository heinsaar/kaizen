#pragma once

#include <string_view>
#include <iostream>
#include <sstream>
#include <random>

namespace zen {

/////////////////////////////////////// USEFUL TRIVIA ///////////////////////////////////////

inline std::string quote(std::string_view s) { return '\"' + std::string(s) + '\"'; }

/////////////////////////////////////////////////////////////////////////////////////////////

template<class T = int>
T random_int(const T min = 0, const T max = 10)
{
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

template<class Collection>
void populate_random(Collection& c, int size = 10)
{
    c.resize(size);
    std::generate(std::begin(c), std::end(c), [&]() { return random_int(10, 99); });
}

/////////////////////////////////////////////////////////////////////////////////////////////

// Check if a type is iterable
template <class T>
constexpr bool is_iterable_v = requires(T x) {
    *std::begin(x); // can be dereferenced
    std::end(x);    // has an end
};

/////////////////////////////////////////////////////////////////////////////////////////////

// Overload for containers like vector, list, etc.
template<class Collection>
std::string to_string(const Collection& c) {
    std::stringstream ss;
    for (const auto& x : c) {
        ss << " " << x;
    }
    return ss.str();
}

// Recursive variadic template to handle multiple arguments
template<class T, class... Args>
std::string to_string(const T& x, const Args&... args) {
    return to_string(x) + " " + to_string(args...);
}
// Base case for the recursive calls
std::string to_string() { return ""; }

// Function to handle individual item printing
template <class T>
void printx(const T& x)
{
    if constexpr (is_iterable_v<T>) {
        std::cout << "[";
        auto it = std::begin(x);
        if (it != std::end(x)) {
            std::cout << *it++;
        }
        for (; it != std::end(x); ++it) {
            std::cout << ", " << *it;
        }
        std::cout << "]";
    }
    else { // not iterable, single item
        std::cout << x;
    }
}

template<class Collection>
void print(const Collection& c)
{
    printx(c);
    std::cout << std::endl;
    //std::cout << to_string(c) << std::endl;
}

// Generic, almost Python-like print(). Works like this:
// print("Hello", "World", vec, 42); // Output: Hello World [1, 2, 3] 42
// print("Hello", "World", 24, vec); // Output: Hello World 24 [1, 2, 3]
// print("Hello", vec, 42, "World"); // Output: Hello [1, 2, 3] 42 World
template <class T, class... Args>
void print(T x, Args... args) {
    printx(x);
    if constexpr (sizeof...(args) != 0) {
        std::cout << " ";
    }
    print(args...);
}
// Base case for the recursive calls
void print() { std::cout << std::endl; }

} // namespace