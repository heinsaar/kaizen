#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_version()
{
    BEGIN_TEST;

    zen::version v1(1, 2, 3, 4567);
    ZEN_EXPECT(v1.major() ==    1);
    ZEN_EXPECT(v1.minor() ==    2);
    ZEN_EXPECT(v1.patch() ==    3);
    ZEN_EXPECT(v1.build() == 4567);

    zen::version v8("8.2.3.4567");
    ZEN_EXPECT(v8.major() ==    8);
    ZEN_EXPECT(v8.minor() ==    2);
    ZEN_EXPECT(v8.patch() ==    3);
    ZEN_EXPECT(v8.build() == 4567);

    ZEN_EXPECT(v1 != v8);
    ZEN_EXPECT(v1 <  v8);
    ZEN_EXPECT(v8 >  v1);

    using namespace zen::literals::version;
    auto v7 = "7.6.5.4321"_version;
    ZEN_EXPECT(v7.build() == 4321);

    std::ostringstream os;
    zen::version v(1, 2, 3, 4);
    os << v;
    ZEN_EXPECT(os.str() == "1.2.3.4");

    ZEN_EXPECT_THROW(zen::version vi("invalid.version"), std::invalid_argument);
}
