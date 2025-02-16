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

// silent_print() is designed to test zen::print()
// Testing zen::print() is a special case since we're testing the same function
// that's also used for test output log. Therefore, in order not to pollute the
// test output log, we save the standard cout buffer into old_buf at the top of
// this function, and restore to it after each test so that each test ends with
// a restoration of the system to printing into the standard output.
// 
// The tests in between juggle around in a way so that ZEN_EXPECT (which uses zen::log(),
// which in turn uses zen::print()) behaves as expected instead of outputting into the
// intermediate stream used for testing the zen::print(). Tests follow this pattern:
// 
// 1. Reset a local std::stringstream object state to an empty string
// 1. Redirect cout into the local std::stringstream object
// 1. Call zen::print(), which will output into the std::stringstream object
// 2. Temporarily redirect cout back to the standard output for the subsequent ZEN_EXPECT()
// 3. Use ZEN_EXPECT() with the standard output

// Modified silent_print to perfectly forward to the variadic print function
template <class... Args>
std::string silent_print(Args&&... args) {
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect the standard output to the local ss
    zen::print(std::forward<Args>(args)...);    // print to the local stream (i.e., "silent")
    std::cout.flush();                          // just in case
    std::cout.rdbuf(old_buf);                   // redirect back to standard output
    return ss.str();
}