#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header

void main_test_filestring()
{
    BEGIN_TEST;

    const auto project_dir = zen::search_upward(std::filesystem::current_path(), "kaizen").value();
    zen::filestring filestr(project_dir / "LICENSE.txt");

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