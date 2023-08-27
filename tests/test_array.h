#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_array()
{
    zen::array<int, 5> a = { 1, 2, 3, 4, 5 };

    assert(a.contains(5));

    std::cout << "TEST PASS: " << __func__ << "() CONTENT" << zen::to_string(a) << std::endl;
}