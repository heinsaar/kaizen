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

///////////////////////////////////////////////////////////////////////////////////////////// CONCEPTS

// ------------------------------------------------------------------------------------------ HasEmpty

#if __cpp_concepts >= 202002L
    // Check if a type T has an empty member function
    template <class T>
    concept HasEmpty = requires(T x) {
        { x.empty() } -> std::same_as<bool>;
    };

    template <typename T> concept has_empty_v = HasEmpty<T>;
#else // use SFINAE if concepts are not available (pre-C++20)
    template <class T, class = void> struct has_empty : std::false_type {};

    template <class T>
    struct has_empty<T,
        std::void_t<decltype(std::declval<T&>().empty())>
    > : std::true_type {
        static_assert(std::is_same_v<decltype(std::declval<T&>().empty()), bool>, "empty() MUST RETURN bool");
    };

    template <class T> constexpr bool has_empty_v = has_empty<T>::value;
#endif

// ------------------------------------------------------------------------------------------ Iterable

#if __cpp_concepts >= 202002L
    // Check if a type is iterable
    template <class T>
    concept Iterable = requires(T x) {
       *std::begin(x); // has begin and can be dereferenced
        std::end(x);   // has an end
    };
    template <typename T> constexpr bool is_iterable_v = Iterable<T>;
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

// ------------------------------------------------------------------------------------------ Addable

#if __cpp_concepts >= 202002L
    template <class T>
    concept Addable = requires(T x, T y) { x + y; };
    template <typename T> concept is_addable_v = Addable<T>;
#else
    template <class T, class = void> struct is_addable : std::false_type {};

    template <class T>
    struct is_addable<T,
        std::void_t<decltype(std::declval<T>() + std::declval<T>())>
    > : std::true_type {};

    template <class T> constexpr bool is_addable_v = is_addable<T>::value;
#endif

// ------------------------------------------------------------------------------------------ Arithmetic

#if __cpp_concepts >= 202002L
    template <class T>
    concept Arithmetic = std::is_arithmetic<T>::value;
    template <typename T> concept is_arithmetic_v = Arithmetic<T>;
#else
    template <class T> struct is_arithmetic : std::is_arithmetic<T> {};
    template <class T> constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
#endif

// ------------------------------------------------------------------------------------------ Resizable

#if __cpp_concepts >= 202002L
    template <class T>
    concept Resizable = requires(T x, size_t n) {
        x.resize(n); // has a resize method
        { x.size() } -> std::same_as<size_t>; // has a size method returning size_t
    };
    template <typename T> concept is_resizable_v = Resizable<T>;
#else
    template <class T, class = void> struct is_resizable : std::false_type {};

    template <class T>
    struct is_resizable<T,
        std::void_t<
            decltype(std::declval<T&>().resize(std::declval<size_t>())), // has a resize method
            decltype(std::declval<T&>().size())                          // has a size method
        >
    > : std::true_type {};

    template <class T> constexpr bool is_resizable_v = is_resizable<T>::value;
#endif

// ------------------------------------------------------------------------------------------ is_string_like

template<class T>
constexpr bool is_string_like() {
    return std::is_convertible<T, std::string>::value
        || std::is_convertible<T, const char*>::value;
}

} // namespace zen