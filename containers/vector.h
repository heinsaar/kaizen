#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include <random>

namespace mas {

template<typename T>
struct vector : std::vector<T>
{
    using std::vector<T>::vector; // Inherit constructors of std::vector<T>

    bool contains(const T& x) const
    {
        return std::find(my::begin(), my::end(), x) != my::end();
    }

    template<typename Pred>
    bool contains(Pred p) const
    {
        return std::find_if(my::begin(), my::end(), p) != my::end();
    }

    void populate_random(const int size)
    {
        my::resize(size);

        // Seed the random number generator
        std::random_device              rd;
        std::mt19937                    gen(rd());
        std::uniform_int_distribution<> dis(0, 100);

        std::generate(my::begin(), my::end(), [&]() { return dis(gen); });
    }

    void print()
    {
        for (int i : *this)
            std::cout << i << " ";
    }

private:
    using my = vector;
};

} // namespace masis