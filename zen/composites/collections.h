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

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// COMPOSITES

// Following are some of the most common data types defined in
// pretty much all C++ projects that use the types on the right.
// The name 'composites' is chosen by analogy with composite materials.

template<
    class T,
    class H = std::hash<T>,
    class E = std::equal_to<T>,
    class A = std::allocator<T>
>
using hash_set = zen::unordered_set<T, H, E, A>;

template<
    class T,
    class H = std::hash<T>,
    class E = std::equal_to<T>,
    class A = std::allocator<T>
>
using hash_multiset = zen::unordered_multiset<T, H, E, A>;

template<
    class K,
    class V,
    class H = std::hash<K>,
    class E = std::equal_to<K>,
    class A = std::allocator<std::pair<const K, V>>
>
using hash_map = zen::unordered_map<K, V, H, E, A>;

template<
    class K,
    class V,
    class H = std::hash<K>,
    class E = std::equal_to<K>,
    class A = std::allocator<std::pair<const K, V>>
>
using hash_multimap = zen::unordered_multimap<K, V, H, E, A>;

// Composite names
using stringlist = zen::list<  zen::string>;
using stringvec  = zen::vector<zen::string>;
using integers   = zen::vector<int>;
using floats     = zen::vector<float>;
using reals      = zen::vector<double>;
using keyval     = zen::map<zen::string, zen::string>;
using points2d   = zen::vector<zen::point2d>;
using points3d   = zen::vector<zen::point3d>;

// Composite name aliases
using dictionary = keyval;
using strings    = stringvec;
using points     = points2d;
using ints       = integers;

} // namespace zen