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

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::set

template<class K, class C = std::less<K>, class A = std::allocator<K>>
class set : public std::set<K, C, A>
{
public:
    using std::set<K, C, A>::set; // inherit constructors, has to be explicit

    bool is_empty() const { return my::empty(); }

private:
    using my = set<K, C, A>;

    // Disable dynamic allocation since this type is derived from its std namesake that's
    // not meant to be derived from (in particular, its destructor is not virtual).
    static void* operator new(  std::size_t) = delete;
    static void* operator new[](std::size_t) = delete;
    static void  operator delete(  void*)    = delete;
    static void  operator delete[](void*)    = delete;
};

///////////////////////////////////////////////////////////////////////////////////////////// zen::multiset

template<class K, class C = std::less<K>, class A = std::allocator<K>>
class multiset : public std::multiset<K, C, A>
{
public:
    using std::multiset<K, C, A>::multiset; // inherit constructors, has to be explicit

    bool is_empty() const { return my::empty(); }

private:
    using my = multiset<K, C, A>;

    // Disable dynamic allocation since this type is derived from its std namesake that's
    // not meant to be derived from (in particular, its destructor is not virtual).
    static void* operator new(  std::size_t) = delete;
    static void* operator new[](std::size_t) = delete;
    static void  operator delete(  void*)    = delete;
    static void  operator delete[](void*)    = delete;
};

} // namespace zen