#pragma once

#include "../build/kaizen.h" // test using generated header: jump with the parachute you folded

void test_empty_args() {
    BEGIN_TEST;
    const char* args[] = { "exename" };
    zen::cmd_args cmdargs(args, 1);
    ZEN_EXPECT(!cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));
}

void test_single_arg_present() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose" };
    zen::cmd_args cmdargs(args, 2);
    cmdargs.accept("-verbose");
    ZEN_EXPECT(cmdargs.is_present());
}

void test_single_arg_not_present() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose" };
    zen::cmd_args cmdargs(args, 2);
    cmdargs.accept("-ignore");
    ZEN_EXPECT(!cmdargs.is_present());
}

void test_multiple_args_present() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(args, 3);
    cmdargs.accept("-verbose").accept("-ignore");
    ZEN_EXPECT(cmdargs.is_present("-verbose"));
    ZEN_EXPECT(cmdargs.is_present("-ignore"));
}

void test_multiple_args_one_missing() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose" };
    zen::cmd_args cmdargs(args, 2);
    cmdargs.accept("-verbose").accept("-ignore");
    ZEN_EXPECT( cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));
}

void test_arg_at() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(args, 3);
    ZEN_EXPECT(   cmdargs.arg_at(0) == "exename");
    ZEN_EXPECT(   cmdargs.arg_at(1) == "-verbose");
    ZEN_EXPECT(   cmdargs.arg_at(2) == "-ignore");
}

void test_first_last_arg() {
    BEGIN_TEST;
    const char* args[] = { "exename", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(args, 3);
    ZEN_EXPECT(   cmdargs.first_arg() == "exename");
    ZEN_EXPECT(   cmdargs.last_arg() == "-ignore");
}

void main_test_cmd_args(int argc, char* argv[])
{
    BEGIN_TEST;
    
    zen::cmd_args        cmdargs(argv, argc);
    const bool verbose = cmdargs.accept("-verbose").is_present();
    const bool absent  = cmdargs.accept("-absent" ).is_present();

    ZEN_EXPECT( cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-absent"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));

    test_multiple_args_one_missing();
    test_single_arg_not_present();
    test_multiple_args_present();
    test_single_arg_present();
    test_first_last_arg();
    test_empty_args();
    test_arg_at();
}