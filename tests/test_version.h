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

    zen::version v8("8.2.3.4567");
    ZEN_EXPECT(v8.major() ==    8);
    ZEN_EXPECT(v8.minor() ==    2);
    ZEN_EXPECT(v8.patch() ==    3);
    ZEN_EXPECT(v8.build() == 4567);

    ZEN_EXPECT(v0 != v8);
    ZEN_EXPECT(v0 <  v8);
    ZEN_EXPECT(v8 >  v0);

    using namespace zen::version_literals;
    auto v2 = "7.6.5.4321"_version;
    ZEN_EXPECT(v2.build() == 4321);
}
