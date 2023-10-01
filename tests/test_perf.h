#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

#include "../internal.h"

volatile int sink; // global variable to prevent loop optimization

void main_test_performance()
{
    BEGIN_TEST;

    const int N = 10'000; // use 1B for Release/optimized mode

    // Benchmarking zen::in loop
    zen::timer tm;
    for (int i : zen::in(N)) {
        sink += i; // simple computation to prevent loop optimization
    }
    auto t1 = tm.stop().duration_string();

    // Benchmarking traditional for-loop
    tm.start();
    for (int i = 0; i < N; ++i) {
        sink += i; // simple computation to prevent loop optimization
    }
    auto t2 = tm.stop().duration_string();

    zen::log("PERF TIME FOR zen::in: ", t1);
    zen::log("PERF TIME FOR RAW LOOP:", t2);

    silent_print(sink); // to ensure it's used
}