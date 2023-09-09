#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void main_test_filestring()
{
    BEGIN_TEST;

    zen::filestring filestr("../LICENSE.txt");

    zen::string version = filestr.getline(1);
    zen::string license = filestr.getline(3);

    // TODO: Add cases here
    ZEN_EXPECT(version.contains("0.0.1"));
    ZEN_EXPECT(license.contains("MIT"));
}