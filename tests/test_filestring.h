#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_filestring()
{
    zen::filestring filestr("../LICENSE.txt");

    zen::string version = filestr.getline(0);
    zen::string license = filestr.getline(2);

    zen::log("Line 3: ", version);
    zen::log("Line 5: ", license);

    zen::log(zen::color::green("TEST PASS:"), __func__);
}