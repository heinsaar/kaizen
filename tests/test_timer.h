#pragma once

#include <cassert>
#include <thread>

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_timer()
{
    BEGIN_TEST;

    zen::timer timer;

    for ([[maybe_unused]] int i : zen::in(100)) {
        // Trim and deflate a string
        zen::string z = "   Trim   me  ";
        std::string s = z.trim(); // from leading & trailing empty spaces

        // C assert instead of ZEN_EXPECT so as not to
        // confuse the different test case counter
        assert(!::isspace(s.front()));
        assert(!::isspace(s.back()));
    }

    timer.stop();

    using namespace std::chrono;

    ZEN_EXPECT(zen::adaptive_duration(timer.duration<nanoseconds>()) == timer.duration_string());

    ZEN_EXPECT(zen::adaptive_duration(nanoseconds(  999)) == "999 nanoseconds"  );
    ZEN_EXPECT(zen::adaptive_duration(nanoseconds( 1000)) ==   "1 microseconds" );
    ZEN_EXPECT(zen::adaptive_duration(microseconds( 999)) == "999 microseconds" );
    ZEN_EXPECT(zen::adaptive_duration(microseconds(1000)) ==   "1 milliseconds" );
    ZEN_EXPECT(zen::adaptive_duration(milliseconds( 999)) == "999 milliseconds" );
    ZEN_EXPECT(zen::adaptive_duration(milliseconds(1000)) ==   "1 seconds"      );
    ZEN_EXPECT(zen::adaptive_duration(seconds(       59)) ==  "59 seconds"      );
    ZEN_EXPECT(zen::adaptive_duration(seconds(       60)) ==   "1 minutes"      );
    ZEN_EXPECT(zen::adaptive_duration(minutes(       59)) ==  "59 minutes"      );
    ZEN_EXPECT(zen::adaptive_duration(minutes(       60)) ==   "1 hours"        );

    constexpr milliseconds ms20{20};
    const auto dur = zen::measure_execution<>(
        [&ms20]{
            std::this_thread::sleep_for(ms20);
        });
    ZEN_EXPECT(zen::adaptive_duration(dur) != "20 milliseconds"); // flaky test: sometimes fails, but that's okay
}