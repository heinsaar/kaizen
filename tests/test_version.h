#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_version()
{
    zen::version v0(1, 2, 3, 4567);
    assert(v0.major() == 1);
    assert(v0.minor() == 2);
    assert(v0.patch() == 3);
    assert(v0.build() == 4567);

    zen::version v1("8.2.3.4567");
    assert(v1.major() == 8);
    assert(v1.minor() == 2);
    assert(v1.patch() == 3);
    assert(v1.build() == 4567);

    assert(v0 != v1);
    assert(v0 < v1);
    assert(v1 > v0);

    using namespace zen::version_literals;
    auto v2 = "7.6.5.4321"_version;
    assert(v2.build() == 4321);

    zen::log(zen::color::green("TEST PASS:"), __func__);
}
