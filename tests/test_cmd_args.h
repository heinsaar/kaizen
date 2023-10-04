#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_cmd_args_empty_args()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe" };
    zen::cmd_args args(argv, 1);
    ZEN_EXPECT(!args.is_present("-verbose"));
    ZEN_EXPECT(!args.is_present("-ignore"));
}

void test_cmd_args_single_arg_present()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args args(argv, 2);
    args.accept("-verbose");
    ZEN_EXPECT(args.is_present());
}

void test_cmd_args_single_arg_not_present()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args args(argv, 2);
    args.accept("-ignore");
    ZEN_EXPECT(!args.is_present());
}

void test_cmd_args_multiple_args_present()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args args(argv, 3);
    args.accept("-verbose").accept("-ignore");
    ZEN_EXPECT(args.is_present("-verbose"));
    ZEN_EXPECT(args.is_present("-ignore"));
}

void test_cmd_args_multiple_args_one_missing()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose" };
    zen::cmd_args args(argv, 2);
    args.accept("-verbose").accept("-ignore");
    ZEN_EXPECT( args.is_present("-verbose"));
    ZEN_EXPECT(!args.is_present("-ignore"));
}

void test_cmd_args_arg_at()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args args(argv, 3);
    ZEN_EXPECT(   args.arg_at(0) == "exe");
    ZEN_EXPECT(   args.arg_at(1) == "-verbose");
    ZEN_EXPECT(   args.arg_at(2) == "-ignore");
}

void test_cmd_args_first_last_arg()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-ignore" };
    zen::cmd_args args(argv, 3);
    ZEN_EXPECT(   args.first() == "exe");
    ZEN_EXPECT(   args.last()  == "-ignore");
}

void test_cmd_args_constructor_exceptions()
{
    BEGIN_SUBTEST;
    // Test negative argc
    try {
        zen::cmd_args args(nullptr, -1);       // expect an exception thrown from ctor
        ZEN_EXPECT("SHOULD NOT REACH THIS LINE");
    } catch (const std::invalid_argument& e) {
        ZEN_EXPECT(std::string(e.what()) == "CONSTRUCTOR ARGUMENT argc MUST BE NON-NEGATIVE");
    }

    // Test nullptr in argv
    const char* args_with_null[] = { "valid", nullptr };
    try {
        zen::cmd_args args(args_with_null, 2); // expect an exception thrown from ctor
        ZEN_EXPECT(false);                     // should not reach this line
    } catch (const std::invalid_argument& e) {
        ZEN_EXPECT(std::string(e.what()) == "CONSTRUCTOR ARGUMENT argv CONTAINS nullptr ELEMENT(S)");
    }
}

void test_cmd_args_uniqueness()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "-verbose", "-verbose" };
    zen::cmd_args args(argv, 3);
    args.accept("-verbose");
    args.accept("-verbose"); // this should have no effect
    args.accept("");         // this should have no effect either
    ZEN_EXPECT(args.count_accepted() == 1);
}

void main_test_cmd_args(int argc, char* argv[])
{
    BEGIN_TEST;
    
    zen::cmd_args        args(argv, argc);
    const bool verbose = args.accept("-verbose").is_present();
    const bool absent  = args.accept("-absent" ).is_present();

    ZEN_EXPECT(verbose == args.is_present("-verbose"));
    ZEN_EXPECT(absent  == args.is_present("-absent"));
    ZEN_EXPECT(!args.is_present("-ignore"));

    test_cmd_args_multiple_args_one_missing();
    test_cmd_args_single_arg_not_present();
    test_cmd_args_constructor_exceptions();
    test_cmd_args_multiple_args_present();
    test_cmd_args_single_arg_present();
    test_cmd_args_first_last_arg();
    test_cmd_args_empty_args();
    test_cmd_args_uniqueness();
    test_cmd_args_arg_at();
}