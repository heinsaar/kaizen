#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include <random>

namespace mas {

template<typename T>
struct vector : std::vector<T>
{
    using std::vector<T>::vector; // inherit constructors of std::vector<T>

    bool contains(const T& x) const
    {
        return std::find(my::begin(), my::end(), x) != my::end();
    }

    template<typename Pred>
    bool contains(Pred p) const
    {
        return std::find_if(my::begin(), my::end(), p) != my::end();
    }

private:
    using my = vector;
};

} // namespace