// MIT License
// 
// Copyright (c) 2023 Leo Heinsaar
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <type_traits>
#include <algorithm>
#include <list>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::list

template<class T, class A = std::allocator<T>>
class list : public std::list<T, A>
{
public:
    using std::list<T, A>::list; // inherit constructors, has to be explicit

    template<class Pred>
    typename std::enable_if<std::is_invocable_r<bool, Pred, const T&>::value, bool>::type
        contains(Pred p) const
    {
        return std::find_if(my::begin(), my::end(), p) != my::end();
    }
    bool contains(const T& x) const { return std::find(   my::begin(), my::end(), x) != my::end(); }

    bool is_empty() const { return my::empty(); }

private:
    using my = list<T, A>;

    // Disable dynamic allocation since this type is derived from its std namesake that's
    // not meant to be derived from (in particular, its destructor is not virtual).
    static void* operator new(  std::size_t) = delete;
    static void* operator new[](std::size_t) = delete;
    static void  operator delete(  void*)    = delete;
    static void  operator delete[](void*)    = delete;
};

} // namespace zen