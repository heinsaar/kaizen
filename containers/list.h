#pragma once

#include <algorithm>
#include <random>
#include <list>

namespace zen {

template<class T>
struct list : std::list<T>
{
    using std::list<T>::list; // inherit constructors of std::list<T>

    bool contains(const T& x) const
    {
        return std::find(my::begin(), my::end(), x) != my::end();
    }

    template<class Pred>
    bool contains(Pred p) const
    {
        return std::find_if(my::begin(), my::end(), p) != my::end();
    }

private:
    using my = list;
};

} // namespace