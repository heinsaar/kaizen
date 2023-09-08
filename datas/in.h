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

///////////////////////////////////////////////////////////////////////////////////////////// zen::in

// This type is meant to be used in range-for loops:
// for (int i : zen::in(5))         // from  0 to  5
// for (int i : zen::in(1, 10))     // from  1 to 10
// for (int i : zen::in(10, 1, -1)) // from 10 to  1, step -1
//
// Note that apart from an intuitive reading, "in"
// can also be thought of standing for "interval"
struct in {
    in(int end)
        : begin_(0), end_(end), step_(1) {}

    in(int begin, int end, int step = 1)
        : begin_(begin), end_(end), step_(step) {}

    struct iterator {
        iterator(int n = 0, int step = 1) : n_(n), step_(step) {}
        iterator& operator++() { n_ += step_; return *this; }
        const int& operator* ()            const { return n_; }
        bool operator!=(const iterator& x) const {
            return (step_ > 0) ? (n_ < x.n_) : (n_ > x.n_);
        }
    private:
        int n_;
        int step_;
    };

    iterator begin() const { return iterator(begin_, step_); }
    iterator end()   const { return iterator(end_,   step_); }

private:
    int begin_;
    int end_;
    int step_;
};

} // namespace zen