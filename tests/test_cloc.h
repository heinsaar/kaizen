#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_cloc()
{
    BEGIN_TEST;

    zen::cloc cloc;
    zen::log(cloc.count({ R"(\.h)" })); // will pick up kaizen.h

    // TODO: Add tests with edge cases. First commit only self-tests this project.
}