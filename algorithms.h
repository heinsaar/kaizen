#pragma once

#include <iostream>
#include <ranges>

namespace mas {

template<class C>
void print(const C& c)
{
    for (const auto& x : c)
        std::cout << x << " ";
}

} // namespace mas