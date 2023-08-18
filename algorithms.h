#pragma once

#include <iostream>
#include <ranges>

namespace mas {

template<class T>
void print(const T& c)
{
    for (const auto& x : c)
        std::cout << x << " ";
}

} // namespace mas