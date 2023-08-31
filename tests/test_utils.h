#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_utils()
{
    zen::log(zen::color::green("TEST PASS:"), __func__);
}