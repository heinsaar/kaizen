#pragma once

#include <cassert>
#include "kaizen.h" // test using generated header: jump with the parachute you folded

void main_test_cloc()
{
    BEGIN_TEST;

    zen::cloc clocA;                                  // by default initialized with current dir
    int locA_kaizen_h = clocA.count({ R"(\.h)" });    // will pick up kaizen.h
    
    zen::cloc clocB(zen::parent_path(), { "build" }); // specify root & subdirs explicitly
    int locB_kaizen_h = clocB.count({ ".h" });        // will pick up kaizen.h

    zen::cloc clocC({ "." });                         // by default, root is current path; specify subdirs (in this case current as ".")
    int locC_kaizen_h = clocC.count({ ".h" });        // will pick up kaizen.h

    ZEN_EXPECT(locA_kaizen_h == locB_kaizen_h);
    ZEN_EXPECT(locB_kaizen_h == locC_kaizen_h);

    // TODO: Add tests with edge cases
}