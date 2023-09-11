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

#include <forward_list>
#include <type_traits>
#include <algorithm>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::forward_list

template<class T>
struct forward_list : std::forward_list<T> // read 'struct' as "extend the interface"
{
    using std::forward_list<T>::forward_list; // inherit constructors, has to be explicit

    template<class Pred>
    typename std::enable_if<std::is_invocable_r<bool, Pred, const T&>::value, bool>::type
        contains(Pred p) const
    {
        return std::find_if(my::begin(), my::end(), p) != my::end();
    }
    bool contains(const T& x) const { return std::find(   my::begin(), my::end(), x) != my::end(); }

    bool is_empty() const { return my::empty(); }

private:
    using my = forward_list;
};

} // namespace zen