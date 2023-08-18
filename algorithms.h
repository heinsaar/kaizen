#pragma once

#include <iostream>
#include <random>
#include <ranges>

namespace mas {

template<class C>
void print(const C& c)
{
    for (const auto& x : c)
        std::cout << x << " ";
}

template<class C>
void populate_random(C& c)
{
    c.resize(11);

    // Seed the random number generator
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    std::generate(std::begin(c), std::end(c), [&]() { return dis(gen); });
}

} // namespace mas