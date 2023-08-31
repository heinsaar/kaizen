#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_string()
{
    std::string s = "[Hello World]";
    zen::string z = s;

    // TODO: Find a better way than asserting: show red FAIL
    assert(z.contains("World"));
    assert(z.extract_between("[", "]").starts_with("Hello"));

    std::string x = z; z = x;

    zen::log(zen::color::green("TEST PASS:"), __func__);
}