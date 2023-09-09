#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_cmd_args(int argc, char* argv[])
{
    zen::log("BEGIN TEST ------------------------------------------------", __func__);
    
    zen::cmd_args        cmdargs(argv, argc);
    const bool verbose = cmdargs.accept("-verbose").is_present();
    const bool absent  = cmdargs.accept("-absent" ).is_present();

    ZEN_EXPECT( cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-absent"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));
}