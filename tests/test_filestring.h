#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_filestring()
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);

    zen::filestring filestr("../LICENSE.txt");

    zen::string version = filestr.getline(1);
    zen::string license = filestr.getline(3);

    // TODO: Add cases here
}