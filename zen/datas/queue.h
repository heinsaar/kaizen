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

#include <queue>

#include "alpha.h" // internal; will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::queue

template<class T, class C = std::deque<T>>
class queue : public std::queue<T, C>// , private zen::stackonly TODO: See why this 'stackonly' suddenly breaks CI builds
{
public:
    using std::queue<T, C>::queue; // inherit constructors, has to be explicit
    
    template<class Iterable>
    queue(const Iterable& c)
    {
        // TODO: The line below breaks non-Windows build on CI, see why
        //ZEN_STATIC_ASSERT(zen::is_iterable_v<Iterable>, "TEMPLATE PARAMETER EXPECTED TO BE Iterable, BUT IS NOT");

        for (const auto& x : c)
            my::push(x);
    }

    bool is_empty() const { return my::empty(); }

private:
    using my = queue<T, C>;
};

///////////////////////////////////////////////////////////////////////////////////////////// zen::priority_queue

template<
    class T,
    class C = std::vector<T>,
    class L = std::less<typename C::value_type>
>
class priority_queue : public std::priority_queue<T, C, L>// , private zen::stackonly TODO: See why this 'stackonly' suddenly breaks CI builds
{
public:
    using std::priority_queue<T, C, L>::priority_queue; // inherit constructors, has to be explicit

    template<class Iterable>
    priority_queue(const Iterable& c)
    {
        // TODO: The line below breaks non-Windows build on CI, see why
        //ZEN_STATIC_ASSERT(zen::is_iterable_v<Iterable>, "TEMPLATE PARAMETER EXPECTED TO BE Iterable, BUT IS NOT");

        for (const auto& x : c)
            my::push(x);
    }

    bool is_empty() const { return my::empty(); }

private:
    using my = priority_queue<T, C, L>;
};

} // namespace zen