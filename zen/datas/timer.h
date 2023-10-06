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

#include <chrono>
#include <functional>

namespace zen {

template <class Rep, class Period>
std::string adaptive_duration(const std::chrono::duration<Rep, Period>& d)
{
    using namespace std::chrono;

    auto duration_ns = duration_cast<nanoseconds>(d).count();

    if (duration_ns >= 3600e9) return std::to_string(duration_cast<hours>       (d).count()) + " hours";
    if (duration_ns >=   60e9) return std::to_string(duration_cast<minutes>     (d).count()) + " minutes";
    if (duration_ns >=    1e9) return std::to_string(duration_cast<seconds>     (d).count()) + " seconds";
    if (duration_ns >=    1e6) return std::to_string(duration_cast<milliseconds>(d).count()) + " milliseconds";
    if (duration_ns >=    1e3) return std::to_string(duration_cast<microseconds>(d).count()) + " microseconds";

    return std::to_string(duration_ns) + " nanoseconds";
}

///////////////////////////////////////////////////////////////////////////////////////////// zen::timer

class timer {
public:
    timer() : start_(std::chrono::high_resolution_clock::now()), 
               stop_(std::chrono::high_resolution_clock::now())
    {}

    auto start() { start_ = std::chrono::high_resolution_clock::now(); return *this; }
    auto stop()  {  stop_ = std::chrono::high_resolution_clock::now(); return *this; }

    template<class Duration>
    auto elapsed() const {
        const auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<Duration>(now - start_);
    }

    template<class Duration>
    auto duration() const {
        return std::chrono::duration_cast<Duration>(stop_ - start_);
    }

    auto duration_string() const {
        return adaptive_duration(duration<nsec>());
    }

    using nsec = std::chrono::nanoseconds;
    using usec = std::chrono::microseconds;
    using msec = std::chrono::milliseconds;
    using sec  = std::chrono::seconds;
    using min  = std::chrono::minutes;
    using hrs  = std::chrono::hours;
  //using d    = std::chrono::days;   // since C++20
  //using w    = std::chrono::weeks;  // since C++20
  //using m    = std::chrono::months; // since C++20
  //using y    = std::chrono::years;  // since C++20

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::chrono::time_point<std::chrono::high_resolution_clock>  stop_;
};

template<typename Duration = timer::nsec>
auto measure_execution(std::function<void()> operation)
{
    timer t;
    operation();
    t.stop();
    return t.duration<Duration>();
}

} // namespace zen