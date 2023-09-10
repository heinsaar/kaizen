#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header

void sanitest_filestring()
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);

    const auto project_dir = zen::search_upward(std::filesystem::current_path(), "kaizen").value();
    zen::filestring filestr(project_dir / "LICENSE.txt");

    zen::string version = filestr.getline(1);
    zen::string license = filestr.getline(3);

    // TODO: Add cases here
    ZEN_EXPECT(version.contains("0.0.1"));
    ZEN_EXPECT(license.contains("MIT"));
}