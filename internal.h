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

/////////////////////////////////////////////////////////////////////////////////
// 
// This file is nternal to Kaizen and its contents do not become part of kaizen.h
//
/////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

template<class T>
std::string silent_print(T&& x)
{
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect the output
    std::cout.rdbuf(ss.rdbuf());                // redirect to a local stream
    zen::print(std::forward<T>(x));             // print to to the local stream (i.e., "silent")
    std::cout.rdbuf(old_buf);                   // redirect back to standard output
    return ss.str();
}