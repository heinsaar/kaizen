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
#include <deque>

#include "alpha.h" // internal; will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::deref

namespace internal {

// Base case: stop dereferencing
template <typename T, typename = void>
struct deref_recursive {
    static T& deref(T& x) { return x; }
};

// Recursive case: continue dereferencing
template <typename T>
struct deref_recursive<T, std::void_t<decltype(*std::declval<T&>())>> {
    static auto deref(T& x) -> decltype(deref_recursive<std::remove_reference_t<decltype(*x)>>::deref(*x)) {
        return                          deref_recursive<std::remove_reference_t<decltype(*x)>>::deref(*x);
    }
};

} // namespace internal

// Main deref function
template <typename T>
auto deref(T& x) -> decltype(internal::deref_recursive<T>::deref(x)) {
    return                   internal::deref_recursive<T>::deref(x);
}

} // namespace zen