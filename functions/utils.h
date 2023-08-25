#pragma once

#include <string_view>
#include <iostream>
#include <sstream>
#include <random>

namespace zen {

template<class T = int>
T random_int(T min = 0, T max = 10)
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
void print(const Collection& c)
{
    std::cout << to_string(c) << std::endl;
}

template<typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t << " ";
    print(args...);
}
// Base case for the recursive calls
void print() { std::cout << std::endl; }

// Overload for containers like vector, list, etc.
template<typename Collection>
std::string to_string(const Collection& c) {
    std::stringstream ss;
    for (const auto& x : c) {
        ss << " " << x;
    }
    return ss.str();
}
// Base case for the recursive calls
std::string to_string() { return ""; }

// Recursive variadic template to handle multiple arguments
template<typename T, typename... Args>
std::string to_string(const T& t, const Args&... args) {
    return to_string(t) + " " + to_string(args...);
}

template<class Collection>
void populate_random(Collection& c, int size = 10)
{
    c.resize(size);
    std::generate(std::begin(c), std::end(c), [&](){ return random_int(0, 100); });
}

/////////////////////////////////////// USEFUL TRIVIA ///////////////////////////////////////

inline std::string quote(std::string_view s) { return '\"' + std::string(s) + '\"'; }

} // namespace