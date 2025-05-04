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

void test_cmd_args_one_arg_with_value()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "--path", "from/some/dir", "to/some/dir" };
    zen::cmd_args args(argv, 4);
    args.accept("--path");
    ZEN_EXPECT(args.is_present("--path"));
    ZEN_EXPECT(
        args.get_options("--path")[0] == "from/some/dir" &&
        args.get_options("--path")[1] ==   "to/some/dir"
    );
}

void test_cmd_args_one_arg_with_no_value()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "--verbose" };
    zen::cmd_args args(argv, 2);
    args.accept("--verbose");
    ZEN_EXPECT(args.is_present("--verbose"));
    ZEN_EXPECT(
        args.get_options("--verbose").empty()
    );
}

void test_cmd_args_multiple_args_with_values()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "--src", "source/dir", "--dst", "dest/dir" };
    zen::cmd_args args(argv, 5);
    args.accept("--src").accept("--dst");
    ZEN_EXPECT(args.is_present("--src"));
    ZEN_EXPECT(args.is_present("--dst"));
    ZEN_EXPECT(
        args.get_options("--src")[0] == "source/dir" &&
        args.get_options("--dst")[0] ==   "dest/dir"
    );
}

void test_cmd_args_arg_followed_by_another_arg()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "--src", "--dst", "dest/dir" };
    zen::cmd_args args(argv, 4);
    args.accept("--src").accept("--dst");
    ZEN_EXPECT(args.is_present("--src"));
    ZEN_EXPECT(args.is_present("--dst"));
    ZEN_EXPECT(
        args.get_options("--src").empty() &&
        args.get_options("--dst")[0] == "dest/dir"
    );
}

void test_cmd_args_original_command()
{
    BEGIN_SUBTEST;
    const char* argv[] = { "exe", "--src", "--dst", "dest/dir" };
    zen::cmd_args args(argv, 4);
    ZEN_EXPECT(args.original_command() == "exe --src --dst dest/dir");
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

    test_cmd_args_arg_followed_by_another_arg();
    test_cmd_args_multiple_args_one_missing();
    test_cmd_args_multiple_args_with_values();
    test_cmd_args_single_arg_not_present();
    test_cmd_args_constructor_exceptions();
    test_cmd_args_multiple_args_present();
    test_cmd_args_one_arg_with_no_value();
    test_cmd_args_single_arg_present();
    test_cmd_args_one_arg_with_value();
    test_cmd_args_original_command();
    test_cmd_args_first_last_arg();
    test_cmd_args_empty_args();
    test_cmd_args_uniqueness();
    test_cmd_args_arg_at();
}