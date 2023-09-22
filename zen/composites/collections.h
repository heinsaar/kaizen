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

#include "../datas/vector.h" // will not be included in kaizen.h
#include "../datas/string.h" // will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// COMPOSITES

// Following are some of the most common data types defined in
// pretty much all C++ projects that use the types on the right.
// The name 'composites' is chosen by analogy with composite materials.

using stringlist = zen::list<  zen::string>;
using stringvec  = zen::vector<zen::string>;
using integers   = zen::vector<int>;
using floats     = zen::vector<float>;
using reals      = zen::vector<double>;

// Aliases
using strings = stringvec;
using ints    = integers;

} // namespace zen