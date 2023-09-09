#pragma once

#include "../build/kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_filestring()
{
    BEGIN_TEST;

    zen::filestring filestr("../LICENSE.txt");

    zen::string version = filestr.getline(1);
    zen::string license = filestr.getline(3);

    // TODO: Add cases here
    ZEN_EXPECT(version.contains("1.0.0.0000"));
    ZEN_EXPECT(license.contains("MIT"));

    zen::string ver = version.extract_version();

    zen::version v(ver);
    ZEN_EXPECT(v.major() ==    1);
    ZEN_EXPECT(v.minor() ==    0);
    ZEN_EXPECT(v.patch() ==    0);
    ZEN_EXPECT(v.build() == 0000);
}