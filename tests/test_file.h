#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_file()
{
    BEGIN_TEST;

    const auto project_dir = zen::search_upward("kaizen").value();

    zen::file lic(project_dir / "LICENSE.txt");

    using namespace zen::literals::path;
    zen::file test_literal("../LICENSE.txt"_path);

    // TODO: This shouldn't compile, zen::file constructor only
    // accepts std::filesystem::path, but it compiles. Why? It was failing
    // to compile, as expected, just a few hours ago. May be a Heisenbug.
    zen::file test_string("../LICENSE.txt");

    zen::string version = lic.getline(1);
    zen::string license = lic.getline(3);

    // TODO: Add cases here
    ZEN_EXPECT(version.contains("0.1.1.0000"));
    ZEN_EXPECT(license.contains("MIT"));

    zen::string ver = version.extract_version();

    zen::version v(ver);
    ZEN_EXPECT(v.major() ==    0);
    ZEN_EXPECT(v.minor() ==    1);
    ZEN_EXPECT(v.patch() ==    1);
    ZEN_EXPECT(v.build() == 0000);

    ZEN_EXPECT_THROW(zen::file f("nosuchfile.txt"_path), std::runtime_error);
}