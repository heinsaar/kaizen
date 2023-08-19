#pragma once

#include <iostream>
#include <sstream>
#include <random>

namespace mas {

template<class C>
void print(const C& c)
{
    std::cout << to_string(c) << std::endl;
}

template<class C>
std::string to_string(const C& c)
{
    std::ostringstream oss;
    for (const auto& x : c)
    {
        oss << x << " ";
    }
    std::string result = oss.str();
    return result.empty() ? result : result.substr(0, result.size() - 1); // remove trailing space if present
}

template<class C>
void populate_random(C& c, int size = 10)
{
    c.resize(size);

    // Seed the random number generator
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    std::generate(std::begin(c), std::end(c), [&]() { return dis(gen); });
}

} // namespace