#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_ifile()
{
    BEGIN_TEST;

    const auto project_dir = zen::search_upward(std::filesystem::current_path(), "kaizen").value();

    zen::file::ifile filestr(project_dir / "LICENSE.txt");

    using namespace zen::file::literals::path;
    zen::file::ifile test_literal("../LICENSE.txt"_path);

    // TODO: This shouldn't compile, zen::ifile constructor only
    // accepts std::filesystem::path, but it compiles. Why? It was failing
    // to compile, as expected, just a few hours ago. May be a Heisenbug.
    zen::file::ifile test_string("../LICENSE.txt");

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