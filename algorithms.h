#pragma once

#include <iostream>
#include <sstream>
#include <random>

namespace zen {

template<typename T = int>
T random_int(T min = 0, T max = 10)
{
    static std::random_device        rd;
    static std::mt19937              gen(rd());
    std::uniform_int_distribution<T> dis(min, max);
    return dis(gen);
}

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
    std::generate(std::begin(c), std::end(c), [&](){ return random_int(0, 100); });
}

} // namespace