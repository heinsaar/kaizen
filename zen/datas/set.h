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

#include <set>

#include "alpha.h" // internal; will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::set

template<class K, class C = std::less<K>, class A = std::allocator<K>>
class set : public std::set<K, C, A>, private zen::stackonly
{
public:
    using std::set<K, C, A>::set; // inherit constructors, has to be explicit

    set(const std::set<K, C, A>& u) : std::set<K, C, A>(u) {}

    template<typename Kx, typename Cx, typename Ax>
    set(const std::set<Kx, Cx, Ax>& u) : std::set<K, C, A>(u.begin(), u.end()) {}

    bool is_empty() const { return my::empty(); }

private:
    using my = set<K, C, A>;
};

///////////////////////////////////////////////////////////////////////////////////////////// zen::multiset

template<class K, class C = std::less<K>, class A = std::allocator<K>>
class multiset : public std::multiset<K, C, A>, private zen::stackonly
{
public:
    using std::multiset<K, C, A>::multiset; // inherit constructors, has to be explicit

    multiset(const std::multiset<K, C, A>& u) : std::multiset<K, C, A>(u) {}

    template<typename Kx, typename Cx, typename Ax>
    multiset(const std::multiset<Kx, Cx, Ax>& u) : std::multiset<K, C, A>(u.begin(), u.end()) {}

    bool is_empty() const { return my::empty(); }

private:
    using my = multiset<K, C, A>;
};

} // namespace zen