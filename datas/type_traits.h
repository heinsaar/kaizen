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

#include <iterator>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// TYPE TRAITS

// ------------------------------------------------------------------------------------------ iterable

#if __cpp_concepts >= 202002L
    // Check if a type is iterable
    template <class T>
    constexpr bool is_iterable_v = requires(T x) {
       *std::begin(x); // has begin and can be dereferenced
        std::end(x);   // has an end
    };
#else // use SFINAE if concepts are not available (pre-C++20)
    template <class T, class = void> struct is_iterable : std::false_type {};

    template <class T>
    struct is_iterable<T,
        std::void_t<
            decltype(*std::begin(std::declval<T&>())), // has begin and can be dereferenced
            decltype( std::end(  std::declval<T&>()))  // has an end
        >
    > : std::true_type {};

    template <class T> constexpr bool is_iterable_v = is_iterable<T>::value;
#endif

// ------------------------------------------------------------------------------------------ is_string_like

    template<class T>
    constexpr bool is_string_like() { // TODO: Make this like the is_iterable_v above for consistency
        return std::is_convertible<T, std::string>::value
            || std::is_convertible<T, const char*>::value;
    }

} // namespace zen