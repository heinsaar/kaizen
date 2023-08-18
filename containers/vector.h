#ifndef MASIS_VECTOR_H
#define MASIS_VECTOR_H

#include <vector>

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

private:
    using my = vector;
};

} // namespace masis

#endif // MASIS_VECTOR_H