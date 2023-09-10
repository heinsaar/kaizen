#pragma once

#include "../build/kaizen.h" // test using generated header: jump with the parachute you folded

void test_empty_args() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe" };
    zen::cmd_args cmdargs(argv, 1);
    ZEN_EXPECT(!cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));
}

void test_single_arg_present() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args cmdargs(argv, 2);
    cmdargs.accept("-verbose");
    ZEN_EXPECT(cmdargs.is_present());
}

void test_single_arg_not_present() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args cmdargs(argv, 2);
    cmdargs.accept("-ignore");
    ZEN_EXPECT(!cmdargs.is_present());
}

void test_multiple_args_present() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(argv, 3);
    cmdargs.accept("-verbose").accept("-ignore");
    ZEN_EXPECT(cmdargs.is_present("-verbose"));
    ZEN_EXPECT(cmdargs.is_present("-ignore"));
}

void test_multiple_args_one_missing() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args cmdargs(argv, 2);
    cmdargs.accept("-verbose").accept("-ignore");
    ZEN_EXPECT( cmdargs.is_present("-verbose"));
    ZEN_EXPECT(!cmdargs.is_present("-ignore"));
}

void test_arg_at() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(argv, 3);
    ZEN_EXPECT(   cmdargs.arg_at(0) == "exe");
    ZEN_EXPECT(   cmdargs.arg_at(1) == "-verbose");
    ZEN_EXPECT(   cmdargs.arg_at(2) == "-ignore");
}

void test_first_last_arg() {
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args cmdargs(argv, 3);
    ZEN_EXPECT(   cmdargs.first_arg() == "exe");
    ZEN_EXPECT(   cmdargs.last_arg()  == "-ignore");
}

void test_constructor_exceptions() {
    BEGIN_SUBTEST;
    // Test negative argc
    try {
        zen::cmd_args cmdargs(nullptr, -1);       // expect an exception thrown from ctor
        ZEN_EXPECT("SHOULD NOT REACH THIS LINE");
    } catch (const std::invalid_argument& e) {
        ZEN_EXPECT(std::string(e.what()) == "CONSTRUCTOR ARGUMENT argc MUST BE NON-NEGATIVE");
    }

    // Test nullptr in argv
    const char* args_with_null[] = { "valid", nullptr };
    try {
        zen::cmd_args cmdargs(args_with_null, 2); // expect an exception thrown from ctor
        ZEN_EXPECT(false); // Should not reach this line
    } catch (const std::invalid_argument& e) {
        ZEN_EXPECT(std::string(e.what()) == "CONSTRUCTOR ARGUMENT argv CONTAINS nullptr ELEMENT(S)");
    }
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
    test_constructor_exceptions();
    test_multiple_args_present();
    test_single_arg_present();
    test_first_last_arg();
    test_empty_args();
    test_arg_at();
}