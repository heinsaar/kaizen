#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_version()
{
    zen::log("BEGIN TEST ------------------------------------------------", __func__);

    zen::version v0(1, 2, 3, 4567);
    ZEN_EXPECT(v0.major() ==    1);
    ZEN_EXPECT(v0.minor() ==    2);
    ZEN_EXPECT(v0.patch() ==    3);
    ZEN_EXPECT(v0.build() == 4567);

    zen::version v1("8.2.3.4567");
    ZEN_EXPECT(v1.major() ==    8);
    ZEN_EXPECT(v1.minor() ==    2);
    ZEN_EXPECT(v1.patch() ==    3);
    ZEN_EXPECT(v1.build() == 4567);

    ZEN_EXPECT(v0 != v1);
    ZEN_EXPECT(v0 <  v1);
    ZEN_EXPECT(v1 >  v0);

    using namespace zen::version_literals;
    auto v2 = "7.6.5.4321"_version;
    ZEN_EXPECT(v2.build() == 4321);
}
