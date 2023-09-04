#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_filestring()
{
    zen::filestring filestr("../LICENSE.txt");

    zen::string version = filestr.getline(1);
    zen::string license = filestr.getline(3);

    zen::log(zen::color::green("TEST PASS:"), __func__,
        "LINE 1:", zen::quote(version),
        "LINE 3:", zen::quote(license)
    );
}