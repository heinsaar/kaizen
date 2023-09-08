#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_cmd_args(int argc, char* argv[])
{
    zen::log("BEGIN TEST------------------------------------------------", __func__);
    
    zen::cmd_args       cmd_args(argv, argc);
    const bool verbose = cmd_args.accept("-verbose").is_present();
    const bool absent  = cmd_args.accept("-absent" ).is_present();

    ZEN_EXPECT( cmd_args.is_present("-verbose"));
    ZEN_EXPECT(!cmd_args.is_present("-absent"));
    ZEN_EXPECT(!cmd_args.is_present("-ignore"));
}