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

#include <algorithm>
#include <array>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::array

template<class T, size_t N>
struct array : std::array<T, N>
{
    using std::array<T, N>::array; // inherit constructors, has to be explicit

    // Custom constructor to handle initializer list
    array(std::initializer_list<T> init_list)
    {
        std::copy(std::begin(init_list), std::end(init_list), my::begin());
    }

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
    using my = array;
};

} // namespace