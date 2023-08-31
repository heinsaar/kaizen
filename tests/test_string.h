#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_string()
{
    std::string s = "Hello World";
    zen::string z = s;

    zen::log(zen::color::green("TEST PASS:"), __func__);
}