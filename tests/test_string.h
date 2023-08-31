#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_string()
{
    std::string s = "Hello World";
    zen::string z = s;

    assert(s.starts_with("Hello")); // TODO: Find a better way than asserting

    zen::log(zen::color::green("TEST PASS:"), __func__);
}