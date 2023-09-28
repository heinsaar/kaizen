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

#include <vector>
#include <map>

#include "alpha.h" // internal; will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::map

template<class K, class V, class C = std::less<K>, class A = std::allocator<std::pair<const K, V>>>
class map : public std::map<K, V, C, A>, private stackonly
{
public:
    using std::map<K, V, C, A>::map; // inherit constructors, has to be explicit

    bool is_empty() const { return my::empty(); }

private:
    using my = map<K, V, C, A>;
};

///////////////////////////////////////////////////////////////////////////////////////////// zen::multimap

template<class K, class V, class C = std::less<K>, class A = std::allocator<std::pair<const K, V>>>
class multimap : public std::multimap<K, V, C, A>, private stackonly
{
public:
    using std::multimap<K, V, C, A>::multimap; // inherit constructors, has to be explicit

    // std::map::operator[] is not defined, but
    // zen::map::operator[] returns an std::vector
    // composed of values corresponding to the parameter key.
    std::vector<V> operator[](const K& key) {
        auto range = my::equal_range(key);
        std::vector<V> values;
        for (auto it = range.first; it != range.second; ++it) {
            values.push_back(it->second);
        }
        return values;
    }

    bool is_empty() const { return my::empty(); }

private:
    using my = multimap<K, V, C, A>;
};

} // namespace zen