#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_string_extract()
{
    BEGIN_SUBTEST;

    zen::string z1 = "[Hello World] 1.2.3";

    ZEN_EXPECT(z1.contains("World"));
    ZEN_EXPECT(z1.extract_between("[", "]").starts_with("Hello"));

    // Extract software version
    zen::string z2 = "Software Version 1.2.3.4";
    std::string s2 = z2.extract_version();
    ZEN_EXPECT(s2 == "1.2.3.4");
    s2 = z2.extract_pattern(R"((\d+\.\d+\.\d+))");
    ZEN_EXPECT(s2 == "1.2.3");

    // Extract date
    zen::string z3 = "Some Date 1/2/2023";
    std::string s3 = z3.extract_date();
    ZEN_EXPECT(s3 == "1/2/2023");
    s3 = z3.extract_pattern(R"((\d+\/\d+\/\d+))");
    ZEN_EXPECT(s3 == "1/2/2023");

    // Extract email address
    zen::string z4 = "Contact us at: support@example.com for more details.";
    std::string s4 = z4.extract_email();
    ZEN_EXPECT(s4 == "support@example.com");
    s4 = z4.extract_pattern(R"((\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b))");
    ZEN_EXPECT(s4 == "support@example.com");

    // Extract URL
    zen::string z5 = "Our website is http://www.example.com";
    std::string s5 = z5.extract_url();
    ZEN_EXPECT(s5 == "http://www.example.com");
    s5 = z5.extract_pattern(R"((https?://[^\s]+))");
    ZEN_EXPECT(s5 == "http://www.example.com");

    // Extract currency (price)
    zen::string z6 = "The cost is $25.99";
    std::string s6 = z6.extract_pattern(R"((\$\d+(\.\d{2})?))");
    ZEN_EXPECT(s6 == "$25.99");

    // Extract hashtags
    zen::string z7 = "Trending topics are #Tech #AI";
    std::string s7 = z7.extract_hashtag();
    ZEN_EXPECT(s7 == "#Tech"); // first hashtag
    s7 = z7.extract_pattern(R"((#\w+))");
    ZEN_EXPECT(s7 == "#Tech"); // first hashtag
    
    // Extract file extension
    zen::string z8 = "The file is image.jpeg";
    std::string s8 = z8.extract_extension();
    ZEN_EXPECT(s8 == ".jpeg");
    s8 = z8.extract_pattern(R"((\.\w+$))");
    ZEN_EXPECT(s8 == ".jpeg");
}

void test_string_substring()
{
    BEGIN_SUBTEST;
    //               012345678912345 
    zen::string z = "Test substrings";
    ZEN_EXPECT(z.substring(  0,   4) == "Test");
    ZEN_EXPECT(z.substring( 10,   3) == "");           // from > to
    ZEN_EXPECT(z.substring(100, 300) == "");           // size() < from < to
    ZEN_EXPECT(z.substring(300, 100) == "");           // size() < to < from
    ZEN_EXPECT(z.substring(  5,   5) == "");           // empty string if indices are same
    ZEN_EXPECT(z.substring(-20,   4) == "Test");
    ZEN_EXPECT(z.substring(  0,  -5) == "Test subst");
    // Negative start, negative end
    ZEN_EXPECT(z.substring(-5,   -2) == "rin");
    ZEN_EXPECT(z.substring(-2,   -5) == "");           // unnatural edge case
    // Negative start, positive end
    ZEN_EXPECT(z.substring(-5,   24) == "rings");      // end out of bounds
    ZEN_EXPECT(z.substring(-24,   4) == "Test");
    // Positive start, negative end
    ZEN_EXPECT(z.substring(0,    -5) == "Test subst");
    ZEN_EXPECT(z.substring(30,   -5) == "");           // unnatural edge case
    // Out of bounds
    ZEN_EXPECT(z.substring( 25,  30) == "");           // both out of bounds
    ZEN_EXPECT(z.substring(-25, -30) == "");           // both out of bounds
    ZEN_EXPECT(z.substring(-30,   4) == "Test");       // start out of bounds
    // Various combinations
    ZEN_EXPECT(z.substring(-5,    5) == "");           // negative to positive that precedes it
    ZEN_EXPECT(z.substring( 5,   -5) == "subst");      // positive to negative that follows it
    // Full string           
    ZEN_EXPECT(z.substring(  0,  50) == "Test substrings");
    ZEN_EXPECT(z.substring(-30,  50) == "Test substrings");
}

void test_string_ends_with()
{
    BEGIN_SUBTEST;

    zen::string z = "Hello";
    ZEN_EXPECT( z.ends_with(""));            // string is not empty, substring is empty
    ZEN_EXPECT( z.ends_with("lo"));          // string ends with the given substring
    ZEN_EXPECT(!z.ends_with("Hel"));         // string does not end with the given substring
    ZEN_EXPECT(!z.ends_with("Hello World")); // substring is longer than the string
    ZEN_EXPECT( z.ends_with("Hello"));       // string and substring are the same

    z = "";
    ZEN_EXPECT( z.ends_with(""));            // string is empty, substring is empty
    ZEN_EXPECT(!z.ends_with("test"));        // string is empty, substring is not empty
}

void test_string_trimming()
{
    BEGIN_SUBTEST;
    // Trim and deflate a string
    zen::string z = "   Trim   me  ";
    std::string s = z.trim(); // from leading & trailing empty spaces
    ZEN_EXPECT(z.is_trimmed());
    ZEN_EXPECT(!::isspace(s.front()));
    ZEN_EXPECT(!::isspace(s.back()));
    ZEN_EXPECT(z.deflate().is_deflated());
    ZEN_EXPECT(z.is_empty() == zen::is_empty(z));

    ZEN_EXPECT(zen::repeat("*", 10) == "**********");
    ZEN_EXPECT(zen::repeat(10, "*") == "**********");

}

void test_string_remove()
{
    BEGIN_SUBTEST;

    zen::string  z1 = "Hello, world!";     // basic
    zen::string  z2 = "world world world"; // multiple occurrences
    zen::string  z3 = "Hello, WORLD!";     // case sensitivity
    zen::string  z4 = "Hello, world!";     // no occurrences
    zen::string  z5 = "Hello  world!";     // remove spaces
    zen::string  z6 = "";                  // empty string
    zen::string  z7 = "world";             // remove entire string
    zen::string  z8 = "Hello, world! Have a good world!";
    zen::string  z9 = "123 123 123";
    zen::string z10 = "aaabbaaa";
    zen::string z12 = "Hello, world! 123";
    zen::string z13 = "Hello, world! 123";
    zen::string z14 = "  extra  spaces  ";
    zen::string z15 = "<tag>content</tag>";
    zen::string z16 = "<tag>content</tag>";
    zen::string z17 = "Hello123World";
        
     z1.remove("world");
     z2.remove("world");
     z3.remove("world");
     z4.remove("earth");
     z5.remove("  ");
     z6.remove("world");
     z7.remove("world");
     z8.remove("world");
     z9.remove("\\d+");
    z10.remove("a*");
    z12.remove("[a-z]+");                        // all lowercase words
    z13.remove("[a-zA-Z0-9]+");                  // all words and numbers
    z14.remove("\\s+");                          // all spaces
    z15.remove("<.*>");                          // greedy match
    z16.remove("<.*?>");                         // lazy match
    z17.remove("\\d{2,3}");                      // 2 to 3 digits

    ZEN_EXPECT(z1 == "Hello, !");
    ZEN_EXPECT(z2 == "  ");
    ZEN_EXPECT(z3 == "Hello, WORLD!");
    ZEN_EXPECT(z4 == "Hello, world!");
    ZEN_EXPECT(z5 == "Helloworld!");
    ZEN_EXPECT(z6 == "");
    ZEN_EXPECT(z7 == "");
    ZEN_EXPECT(z8 == "Hello, ! Have a good !");  // pattern 'world' should be removed
    ZEN_EXPECT(z9 == "  ");                      // pattern '\\d+' should remove all digits
    ZEN_EXPECT(z10 == "bb");                     // pattern 'a*' should remove all 'a'
    ZEN_EXPECT(z12 == "H, ! 123");               // pattern '[a-z]+' should remove all lowercase words
    ZEN_EXPECT(z13 == ", ! ");                   // pattern '[a-zA-Z0-9]+' should remove all words and numbers
    ZEN_EXPECT(z14 == "extraspaces");            // pattern '\\s+' should remove all extra spaces
    ZEN_EXPECT(z15 == "");                       // pattern '<.*>' should remove everything
    ZEN_EXPECT(z16 == "content");                // pattern '<.*?>' should remove all tags but leave content
    ZEN_EXPECT(z17 == "HelloWorld");             // pattern '\\d{2,3}' should remove 123
}

void test_string_pad_end()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hey";
    zen::string z2 = "Hey";
    zen::string z3 = "Hey";
    zen::string z4 = "Hey";
    zen::string z5 = "Hey";
    zen::string z6 = "Hey";
    zen::string z7 = "Hey";
    zen::string z8 = "";

    z1.pad_end(5);          // padding with default space character
    z2.pad_end(6, "AB");    // padding with a custom string
    z3.pad_end(8, "ABCDE"); // padding with a longer custom string
    z4.pad_end(2);          // with a target_length smaller than the string size (no change expected)
    z5.pad_end(3);          // with a target_length equal to the string size (no change expected)
    z6.pad_end(5, "");      // padding with an empty string (no change expected)
    z7.pad_end(7, "AB");    // padding with multiple characters, but not enough to complete the next repeat
    z8.pad_end(3, "A");     // padding an empty string

    ZEN_EXPECT(z1 == "Hey  ");
    ZEN_EXPECT(z2 == "HeyABA");
    ZEN_EXPECT(z3 == "HeyABCDE");
    ZEN_EXPECT(z4 == "Hey");
    ZEN_EXPECT(z5 == "Hey");
    ZEN_EXPECT(z6 == "Hey");
    ZEN_EXPECT(z7 == "HeyABAB");
    ZEN_EXPECT(z8 == "AAA");
}

void test_string_pad_start()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hey";
    zen::string z2 = "Hey";
    zen::string z3 = "Hey";
    zen::string z4 = "Hey";
    zen::string z5 = "Hey";
    zen::string z6 = "Hey";
    zen::string z7 = "Hey";
    zen::string z8 = "";

    z1.pad_start(5);          // padding with default space character
    z2.pad_start(6, "AB");    // padding with a custom string
    z3.pad_start(8, "ABCDE"); // padding with a longer custom string
    z4.pad_start(2);          // target_length smaller than the string size
    z5.pad_start(3);          // target_length equal to the string size
    z6.pad_start(5, "");      // padding with an empty string
    z7.pad_start(7, "AB");    // padding with multiple characters, but not enough to complete the next repeat
    z8.pad_start(3, "A");     // padding an empty string

    ZEN_EXPECT(z1 == "  Hey");
    ZEN_EXPECT(z2 == "ABAHey");
    ZEN_EXPECT(z3 == "ABCDEHey");
    ZEN_EXPECT(z4 == "Hey");
    ZEN_EXPECT(z5 == "Hey");
    ZEN_EXPECT(z6 == "Hey");
    ZEN_EXPECT(z7 == "ABABHey");
    ZEN_EXPECT(z8 == "AAA");
}

void test_string_replace_if()
{
    zen::string z1  = "I love apples.";
    zen::string z2  = "Replace me, replace me!";
    zen::string z3  = "Nothing to replace here.";
    zen::string z4  = "No change.";
    zen::string z5  = "Remove me.";
    zen::string z6  = "No change.";
    zen::string z7  = "CaseSensitive";
    zen::string z8  = "ReplaceAll";
    zen::string z9  = "Short";
    zen::string z10 = "Lengthy";
    zen::string z11 = "EndReplace";

    // Attempt replacement, and the predicate returns true.
    z1.replace_if("apples", "oranges", [](const zen::string&){ return true; });
    ZEN_EXPECT(z1 == "I love oranges.");

    // Attempt replacement, but the predicate returns false, so no replacement should occur.
    z2.replace_if("replace", "REPLACED", [](const zen::string&){ return false; });
    ZEN_EXPECT(z2 == "Replace me, replace me!");

    // Attempt replacement, and the predicate returns true.
    z3.replace_if("replace", "REPLACED", [](const zen::string&){ return true; });
    ZEN_EXPECT(z3 == "Nothing to REPLACED here.");

    // Attempt replacement with an empty search string, and the predicate returns true.
    z4.replace_if("", "REPLACED", [](const zen::string&){ return true; });
    ZEN_EXPECT(z4 == "No change.");

    // Attempt removal using a predicate, and the predicate returns true.
    z5.replace_if("Remove ", "", [](const zen::string&){ return true; });
    ZEN_EXPECT(z5 == "me.");

    // Attempt removal using a predicate, but the predicate returns false, so no replacement should occur.
    z6.replace_if("", "", [](const zen::string&){ return false; });
    ZEN_EXPECT(z6 == "No change.");

    // Case-sensitive replacement, and the predicate returns true.
    z7.replace_if("Case", "CASE", [](const zen::string&){ return true; });
    ZEN_EXPECT(z7 == "CASESensitive");

    // Attempt replacement, and the predicate returns true.
    z8.replace_if("ReplaceAll", "AllReplaced", [](const zen::string&){ return true; });
    ZEN_EXPECT(z8 == "AllReplaced");

    // Predicate returns true, so the replacement should occur.
    z9.replace_if("Short", "Lengthy", [](const zen::string&){ return true; });
    ZEN_EXPECT(z9 == "Lengthy");

    // Predicate returns false, so no replacement should occur.
    z10.replace_if("Lengthy", "Short", [](const zen::string&){ return false; });
    ZEN_EXPECT(z10 == "Lengthy");

    // Attempt replacement, but the predicate returns false, so no replacement should occur.
    z11.replace_if("Replace", "Replaced", [](const zen::string&){ return false; });
    ZEN_EXPECT(z11 == "EndReplace");
}

void test_string_replace_all_if() {
    zen::string z1 = "Apple, banana, and apricot are fruits.";
    zen::string z2 = "The cat chased the rat. CATapult!";
    zen::string z3 = "1234567890";
    zen::string z4 = "abcdeabcde";
    zen::string z5 = "abcde";
    zen::string z6 = "";

    // Replace all occurrences if the string starts with 'A'
    z1.replace_all_if("a", "X", [](const std::string& s) { return !s.empty() && s[0] == 'A'; });
    ZEN_EXPECT(z1 == "Apple, bXnXnX, Xnd Xpricot Xre fruits.");

    // Replace all occurrences if the string contains 'cat'
    z2.replace_all_if("cat", "DOG", [](const std::string& s) { return s.find("cat") != std::string::npos; });
    ZEN_EXPECT(z2 == "The DOG chased the rat. CATapult!");

    // No replacements should occur when the predicate always returns false
    z3.replace_all_if("1", "X", [](const std::string&) { return false; });
    ZEN_EXPECT(z3 == "1234567890");

    // Replace all occurrences with an empty string
    z4.replace_all_if("cde", "", [](const std::string&) { return true; });
    ZEN_EXPECT(z4 == "abab");

    // No replacements should occur when the search string is empty
    z5.replace_all_if("", "X", [](const std::string&) { return true; });
    ZEN_EXPECT(z5 == "abcde");

    // Empty string
    z6.replace_all_if("abc", "XYZ", [](const std::string&) { return true; });
    ZEN_EXPECT(z6 == ""); // No change expected
}

void test_string_replace_all()
{
    BEGIN_SUBTEST;

    zen::string z1 = "AAA";
    zen::string z2 = "abcabc";
    zen::string z3 = "abcabc";
    zen::string z4 = "abcabc";
    zen::string z5 = "abcabc";
    zen::string z6 = "abcabc";
    zen::string z7 = "abcabc";
    zen::string z8 = "abcdefabcdef";
    zen::string z9 = "";

    z1.replace_all("A",      "B");
    z2.replace_all("abc",    "abcdef");
    z3.replace_all("abc",    "a");
    z4.replace_all("abc",    "");
    z5.replace_all("",       "xyz");
    z6.replace_all("xyz",    "123");
    z7.replace_all("abc",    "abc");
    z8.replace_all("abcdef", "abc");
    z9.replace_all("abc",    "123");

    ZEN_EXPECT(z1 == "BBB");
    ZEN_EXPECT(z2 == "abcdefabcdef");
    ZEN_EXPECT(z3 == "aa");
    ZEN_EXPECT(z4 == "");
    ZEN_EXPECT(z5 == "abcabc");
    ZEN_EXPECT(z6 == "abcabc");
    ZEN_EXPECT(z7 == "abcabc");
    ZEN_EXPECT(z8 == "abcabc");
    ZEN_EXPECT(z9 == "");
}

void test_string_replace()
{
    zen::string z1  = "I love apples.";
    zen::string z2  = "Replace me, replace me!";
    zen::string z3  = "Nothing to replace here.";
    zen::string z4  = "No change.";
    zen::string z5  = "Remove me.";
    zen::string z6  = "No change.";
    zen::string z7  = "CaseSensitive";
    zen::string z8  = "ReplaceAll";
    zen::string z9  = "Short";
    zen::string z10 = "Lengthy";
    zen::string z11 = "EndReplace";

    z1.replace("apples",     "oranges");
    z2.replace("replace",    "REPLACED");
    z3.replace("replace",    "REPLACED");
    z4.replace("",           "REPLACED");
    z5.replace("Remove ",    "");
    z6.replace("",           "");
    z7.replace("case",       "CASE");
    z8.replace("ReplaceAll", "AllReplaced");
    z9.replace("Short",      "Lengthy");
    z10.replace("Lengthy",   "Short");
    z11.replace("Replace",   "Replaced");

    ZEN_EXPECT(z1 == "I love oranges.");
    ZEN_EXPECT(z2 == "Replace me, REPLACED me!");
    ZEN_EXPECT(z3 == "Nothing to REPLACED here.");
    ZEN_EXPECT(z4 == "REPLACEDNo change.");
    ZEN_EXPECT(z5 == "me.");
    ZEN_EXPECT(z6 == "No change.");
    ZEN_EXPECT(z7 == "CaseSensitive");
    ZEN_EXPECT(z8 == "AllReplaced");
    ZEN_EXPECT(z9 == "Lengthy");
    ZEN_EXPECT(z10 == "Short");
    ZEN_EXPECT(z11 == "EndReplaced");
}

void test_string_capitalize() {
    zen::string str1 = "hello world";
    zen::string str2 = ""; 
    zen::string str3 = "this is a test";
    zen::string str4 = "THIS IS ANOTHER TEST";
    zen::string str5 = "x";
    zen::string str6 = "12345 !@#";
    zen::string str7 = "MiXeD CaSe";
    zen::string str8 = "!hello #world$";
    zen::string str9 = "  leading spaces";
    zen::string str10 = "trailing spaces  ";
    zen::string str11 = "aL";

    str1.capitalize();
    ZEN_EXPECT(str1 == "Hello world");

    str2.capitalize();
    ZEN_EXPECT(str2 == "");

    str3.capitalize();
    ZEN_EXPECT(str3 == "This is a test");

    str4.capitalize();
    ZEN_EXPECT(str4 == "This is another test");

    str5.capitalize();
    ZEN_EXPECT(str5 == "X");

    str6.capitalize();
    ZEN_EXPECT(str6 == "12345 !@#");

    str7.capitalize();
    ZEN_EXPECT(str7 == "Mixed case");

    str8.capitalize();
    ZEN_EXPECT(str8 == "!hello #world$");

    str9.capitalize();
    ZEN_EXPECT(str9 == "  leading spaces");

    str10.capitalize();
    ZEN_EXPECT(str10 == "Trailing spaces  ");

    str11.capitalize();
    ZEN_EXPECT(str11 == "Al");
}

void test_string_to_lower() {
    zen::string z1 = "Hello World!";
    zen::string z2 = "123 ABC xyz";
    zen::string z3 = "nochange";
    zen::string z4 = "UPPERCASE";
    zen::string z5 = "";
    zen::string z6 = "!@#$%^&*()";
    zen::string z7 = "12345";
    zen::string z8 = "Hello\nWorld";

    z1.to_lower();
    ZEN_EXPECT(z1 == "hello world!");

    z2.to_lower();
    ZEN_EXPECT(z2 == "123 abc xyz");

    z3.to_lower();
    ZEN_EXPECT(z3 == "nochange");

    z4.to_lower();
    ZEN_EXPECT(z4 == "uppercase");

    z5.to_lower();
    ZEN_EXPECT(z5 == "");

    z6.to_lower();
    ZEN_EXPECT(z6 == "!@#$%^&*()");

    z7.to_lower();
    ZEN_EXPECT(z7 == "12345");

    z8.to_lower();
    ZEN_EXPECT(z8 == "hello\nworld");
}

void test_string_to_upper() {
    zen::string z1 = "Hello World!";
    zen::string z2 = "123 abc XYZ";
    zen::string z3 = "NOCHANGE";
    zen::string z4 = "";
    zen::string z5 = "!@#$%^&*()";
    zen::string z6 = "123!@#";
    zen::string z7 = "MixedCASE123";
    zen::string z8 = "Hello\nWorld";

    z1.to_upper();
    ZEN_EXPECT(z1 == "HELLO WORLD!");

    z2.to_upper();
    ZEN_EXPECT(z2 == "123 ABC XYZ");

    z3.to_upper();
    ZEN_EXPECT(z3 == "NOCHANGE");

    z4.to_upper();
    ZEN_EXPECT(z4 == "");

    z5.to_upper();
    ZEN_EXPECT(z5 == "!@#$%^&*()");

    z6.to_upper();
    ZEN_EXPECT(z6 == "123!@#");

    z7.to_upper();
    ZEN_EXPECT(z7 == "MIXEDCASE123");

    z8.to_upper();
    ZEN_EXPECT(z8 == "HELLO\nWORLD");
}

void test_string_center() {
    zen::string z1 = "Hello";
    zen::string z2 = "Centered";
    zen::string z3 = "Wide";
    zen::string z4 = "X";
    zen::string z5 = "";
    zen::string z6 = "Zen";
    zen::string z7 = "WideWord";
    zen::string z8 = "Padded";

    z1.center(10);
    ZEN_EXPECT(z1 == "  Hello   ");

    z2.center(12, '-');
    ZEN_EXPECT(z2 == "--Centered--");

    z3.center(10, '*');
    ZEN_EXPECT(z3 == "***Wide***");

    z4.center(5);
    ZEN_EXPECT(z4 == "  X  ");

    z5.center(8);
    ZEN_EXPECT(z5 == "        ");

    z6.center(10, '+');
    ZEN_EXPECT(z6 == "+++Zen++++");

    z7.center(5, '-');
    ZEN_EXPECT(z7 == "WideWord");

    z8.center(10, '\n');
    ZEN_EXPECT(z8 == "\n\nPadded\n\n");
}

void test_string_is_alnum() {
    zen::string z1 = "Hello123";
    zen::string z2 = "Testing";
    zen::string z3 = "12345";
    zen::string z4 = "!@#$%^";
    zen::string z5 = " ";
    zen::string z6 = "AaBbCc";
    zen::string z7 = "123 456";
    zen::string z8 = "Alphanumeric_123";
    zen::string z9 = "Special-Characters!";
    zen::string z10 = "";

    ZEN_EXPECT(z1.is_alnum() == true);      // Test 1: Alphanumeric
    ZEN_EXPECT(z2.is_alnum() == true);      // Test 2: Alphabetic
    ZEN_EXPECT(z3.is_alnum() == true);      // Test 3: Numeric
    ZEN_EXPECT(z4.is_alnum() == false);     // Test 4: Special characters
    ZEN_EXPECT(z5.is_alnum() == false);     // Test 5: Empty string
    ZEN_EXPECT(z6.is_alnum() == true);      // Test 6: Alphabetic mixed case
    ZEN_EXPECT(z7.is_alnum() == false);     // Test 7: Alphanumeric with space
    ZEN_EXPECT(z8.is_alnum() == false);     // Test 8: Alphanumeric with underscore
    ZEN_EXPECT(z9.is_alnum() == false);     // Test 9: Special characters with exclamation mark
    ZEN_EXPECT(z10.is_alnum() == false);    // Test 10: Empty string
}

void test_string_is_alpha() {
    zen::string z1 = "Hello";
    zen::string z2 = "Testing123";
    zen::string z3 = "12345";
    zen::string z4 = "!@#$%^";
    zen::string z5 = " ";
    zen::string z6 = "AaBbCc";
    zen::string z7 = "With Space Inside";
    zen::string z8 = "Alpha$Characters";
    zen::string z9 = "";

    ZEN_EXPECT(z1.is_alpha() == true);      // Test 1: Alphabetic only (all characters are letters)
    ZEN_EXPECT(z2.is_alpha() == false);     // Test 2: Alphanumeric (contains both letters and numbers)
    ZEN_EXPECT(z3.is_alpha() == false);     // Test 3: Numeric only (all characters are numbers)
    ZEN_EXPECT(z4.is_alpha() == false);     // Test 4: Special characters only (contains special characters)
    ZEN_EXPECT(z5.is_alpha() == false);     // Test 5: Space only (contains only space)
    ZEN_EXPECT(z6.is_alpha() == true);      // Test 6: Alphabetic mixed case (contains letters in mixed case)
    ZEN_EXPECT(z7.is_alpha() == false);     // Test 7: Alphabetic with spaces inside (contains letters with spaces)
    ZEN_EXPECT(z8.is_alpha() == false);     // Test 8: Alphabetic with special characters (contains letters with special characters)
    ZEN_EXPECT(z9.is_alpha() == false);    // Test 9: Empty string
}

void test_string_is_decimal() {
    zen::string z1 = "12345";
    zen::string z2 = "\u0030"; // This is the Unicode representation of '0'
    zen::string z3 = "Testing123";
    zen::string z4 = "!@#$%^";
    zen::string z5 = " ";
    zen::string z6 = "AaBbCc";
    zen::string z7 = "";
    zen::string z8 = "\u0041"; // This is the Unicode representation of 'A'
    zen::string z9 = "0012345";
    zen::string z10 = "123456789012345678901234567890";

    ZEN_EXPECT(z1.is_decimal() == true); // Test 1: Numeric characters (all characters are decimal digits)
    ZEN_EXPECT(z2.is_decimal() == true); // Test 2: Unicode representation of '0' (should also be considered decimal)
    ZEN_EXPECT(z3.is_decimal() == false); // Test 3: Alphanumeric (contains both letters and numbers)
    ZEN_EXPECT(z4.is_decimal() == false); // Test 4: Special characters only (contains special characters)
    ZEN_EXPECT(z5.is_decimal() == false); // Test 5: Space only (contains only space)
    ZEN_EXPECT(z6.is_decimal() == false); // Test 6: Alphabetic mixed case (contains letters in mixed case)
    ZEN_EXPECT(z7.is_decimal() == false); // Test 7: empty case (contains letters in mixed case)
    ZEN_EXPECT(z8.is_decimal() == false); // Test 8: Unicode representation of 'A' (should not be considered decimal)
    ZEN_EXPECT(z9.is_decimal() == true);  // Test 9: Leading zeros (should be considered decimal)
    ZEN_EXPECT(z10.is_decimal() == true); // Test 10: Long string (should be considered decimal)
}

void test_string_is_digit() {
    zen::string z1 = "12345";
    zen::string z2 = "\u0030"; // This is the Unicode representation of '0'
    zen::string z3 = "Testing123";
    zen::string z4 = "!@#$%^";
    zen::string z5 = " ";
    zen::string z6 = "AaBbCc";
    zen::string z7 = "";
    zen::string z8 = "\u0041"; // This is the Unicode representation of 'A'
    zen::string z9 = "0012345";
    zen::string z10 = "123456789012345678901234567890";

    ZEN_EXPECT(z1.is_digit() == true); // Test 1: Numeric characters (all characters are decimal digits)
    ZEN_EXPECT(z2.is_digit() == true); // Test 2: Unicode representation of '0' (should also be considered decimal)
    ZEN_EXPECT(z3.is_digit() == false); // Test 3: Alphanumeric (contains both letters and numbers)
    ZEN_EXPECT(z4.is_digit() == false); // Test 4: Special characters only (contains special characters)
    ZEN_EXPECT(z5.is_digit() == false); // Test 5: Space only (contains only space)
    ZEN_EXPECT(z6.is_digit() == false); // Test 6: Alphabetic mixed case (contains letters in mixed case)
    ZEN_EXPECT(z7.is_digit() == false); // Test 7: empty case (contains letters in mixed case)
    ZEN_EXPECT(z8.is_digit() == false); // Test 8: Unicode representation of 'A' (should not be considered decimal)
    ZEN_EXPECT(z9.is_digit() == true);  // Test 9: Leading zeros (should be considered decimal)
    ZEN_EXPECT(z10.is_digit() == true); // Test 10: Long string (should be considered decimal)
}

void test_string_is_identifier() {
    zen::string z1 = "variable123"; // Test 1: Starts with a letter (valid identifier)
    zen::string z2 = "123variable"; // Test 2: Starts with a digit (invalid identifier)
    zen::string z3 = "var_iable";   // Test 3: Contains underscore (valid identifier)
    zen::string z4 = "var iable";    // Test 4: Contains space (invalid identifier)
    zen::string z5 = "var!able";     // Test 5: Contains special character (invalid identifier)
    zen::string z6 = "_variable";    // Test 6: Starts with an underscore (valid identifier)
    zen::string z7 = "";             // Test 7: Empty string (not a valid identifier)
    zen::string z8 = " ";             // Test 7: Empty string (not a valid identifier)

    ZEN_EXPECT(z1.is_identifier() == true);
    ZEN_EXPECT(z2.is_identifier() == false);
    ZEN_EXPECT(z3.is_identifier() == true);
    ZEN_EXPECT(z4.is_identifier() == false);
    ZEN_EXPECT(z5.is_identifier() == false);
    ZEN_EXPECT(z6.is_identifier() == true);
    ZEN_EXPECT(z7.is_identifier() == false);
    ZEN_EXPECT(z8.is_identifier() == false);
}

void test_string_is_lower() {
    zen::string z1 = "lowercase";    // Test 1: All lowercase characters (valid)
    zen::string z2 = "MiXeDCaSe";   // Test 2: Mixed case characters (invalid, contains uppercase)
    zen::string z3 = "12345";       // Test 4: Digits (invalid, contains digits)
    zen::string z4 = "lower case";   // Test 5: Space (invalid, contains space)
    zen::string z5 = "lower-case";   // Test 6: Hyphen (invalid, contains special character)
    zen::string z6 = "";             // Test 7: Empty string ()
    zen::string z7 = " ";            // Test 8: Space (invalid, contains space)
    zen::string z8 = "lowercase1234"; // Test 9: Digits (invalid, contains digits)

    ZEN_EXPECT(z1.is_lower() == true);
    ZEN_EXPECT(z2.is_lower() == false);
    ZEN_EXPECT(z3.is_lower() == false);
    ZEN_EXPECT(z4.is_lower() == false);
    ZEN_EXPECT(z5.is_lower() == false);
    ZEN_EXPECT(z6.is_lower() == false);
    ZEN_EXPECT(z7.is_lower() == false);
    ZEN_EXPECT(z8.is_lower() == false);
}

void test_string_is_upper() {
    zen::string z1 = "HELLO";            // Test 1: All uppercase characters
    zen::string z2 = "hello";            // Test 2: All lowercase characters
    zen::string z3 = "HeLLo";            // Test 3: Mixed case
    zen::string z4 = "12345";            // Test 4: All digits
    zen::string z5 = " ";                // Test 5: Space character
    zen::string z6 = "!@#$%^";           // Test 6: Special characters
    zen::string z7 = "HELLO world";      // Test 7: Mixed case with space
    zen::string z8 = "HELLO123";         // Test 8: Uppercase and digits
    zen::string z9 = "";                // Test 12: Empty string
    zen::string z10 = " ";               // Test 13: Space character
    zen::string z11 = "\u0061\u0061"; // Test 14: Unicode representation of ''
    zen::string z12 = "\u0041\u0041"; // Test 14: Unicode representation of ''

    ZEN_EXPECT(z1.is_upper() == true);
    ZEN_EXPECT(z2.is_upper() == false);
    ZEN_EXPECT(z3.is_upper() == false);
    ZEN_EXPECT(z4.is_upper() == false);
    ZEN_EXPECT(z5.is_upper() == false);
    ZEN_EXPECT(z6.is_upper() == false);
    ZEN_EXPECT(z7.is_upper() == false);
    ZEN_EXPECT(z8.is_upper() == false);
    ZEN_EXPECT(z9.is_upper() == false);
    ZEN_EXPECT(z10.is_upper() == false);
    ZEN_EXPECT(z11.is_upper() == false);
    ZEN_EXPECT(z12.is_upper() == true);
}

void test_string_is_printable() {
    zen::string z1 = "Hello, World!";    // Test 1: Printable characters (no control characters)
    zen::string z2 = "\n";              // Test 2: Newline character (control character)
    zen::string z3 = "12345";           // Test 3: Digits (printable)
    zen::string z4 = "!@#$%^";          // Test 4: Special characters (printable)
    zen::string z5 = "\t";              // Test 5: Tab character (control character)
    zen::string z6 = " ";               // Test 6: Space character (printable)
    zen::string z7 = "\x7F";            // Test 7: Delete character (control character)
    zen::string z8 = "\x1F";            // Test 8: Unit separator character (control character)
    zen::string z9 = "ᾭᾮᾯ";             // Test 9: Unicode characters (non-ASCII)
    zen::string z10 = "\u03A9";         // Test 10: Unicode character (Ω)
    zen::string z11 = "\u0010";         // Test 11: Data Link Escape (control character)
    zen::string z12 = "";               // Test 12: Empty string

    ZEN_EXPECT(z1.is_printable() == true);
    ZEN_EXPECT(z2.is_printable() == false);
    ZEN_EXPECT(z3.is_printable() == true);
    ZEN_EXPECT(z4.is_printable() == true);
    ZEN_EXPECT(z5.is_printable() == false);
    ZEN_EXPECT(z6.is_printable() == true);
    ZEN_EXPECT(z7.is_printable() == false);
    ZEN_EXPECT(z8.is_printable() == false);
    ZEN_EXPECT(z9.is_printable() == false);
    ZEN_EXPECT(z10.is_printable() == false);
    ZEN_EXPECT(z11.is_printable() == false);
    ZEN_EXPECT(z12.is_printable() == true);
}

void test_string_is_space() {
    zen::string z1 = "   ";           // Test 1: All spaces
    zen::string z2 = "Hello World";    // Test 2: Contains non-space characters
    zen::string z3 = "\t\n\r";         // Test 3: Various whitespace characters
    zen::string z4 = "";               // Test 4: Empty string
    zen::string z5 = "NoSpacesHere";   // Test 5: No spaces at all

    ZEN_EXPECT(z1.is_space() == true);
    ZEN_EXPECT(z2.is_space() == false);
    ZEN_EXPECT(z3.is_space() == true);
    ZEN_EXPECT(z4.is_space() == false);
    ZEN_EXPECT(z5.is_space() == false);
}

void test_string_ljust() {
    zen::string z1 = "Hello";
    zen::string z2 = "123";
    zen::string z3 = "Short";
    zen::string z4 = "";
    zen::string z5 = "ThisIsALongerString";
    zen::string z6 = "negative";

    // Test 1: Left-justify with space padding
    z1.ljust(10);
    ZEN_EXPECT(z1 == "Hello     ");

    // Test 2: Left-justify with '0' padding
    z2.ljust(5, '0');
    ZEN_EXPECT(z2 == "12300");

    // Test 3: Left-justify a shorter string with space padding
    z3.ljust(5);
    ZEN_EXPECT(z3 == "Short");

    // Test 4: Left-justify an empty string with space padding
    z4.ljust(5);
    ZEN_EXPECT(z4 == "     ");

    // Test 5: Left-justify a longer string, no padding needed
    z5.ljust(20);
    ZEN_EXPECT(z5 == "ThisIsALongerString ");

    z6.ljust(-1);
    ZEN_EXPECT(z6 == "negative");
}

void test_string_rjust() {
    zen::string z1 = "Hello";
    zen::string z2 = "123";
    zen::string z3 = "Short";
    zen::string z4 = "";
    zen::string z5 = "ThisIsALongerString";
    zen::string z6 = "negative";

    // Test 1: Left-justify with space padding
    z1.rjust(10);
    ZEN_EXPECT(z1 == "     Hello");

    // Test 2: Left-justify with '0' padding
    z2.rjust(5, '0');
    ZEN_EXPECT(z2 == "00123");

    // Test 3: Left-justify a shorter string with space padding
    z3.rjust(5);
    ZEN_EXPECT(z3 == "Short");

    // Test 4: Left-justify an empty string with space padding
    z4.rjust(5);
    ZEN_EXPECT(z4 == "     ");

    // Test 5: Left-justify a longer string, no padding needed
    z5.rjust(20);
    ZEN_EXPECT(z5 == " ThisIsALongerString");

    z6.rjust(-1);
    ZEN_EXPECT(z6 == "negative");
}

void test_string_rstrip() {
    zen::string z1 = "Hello, World!  \t  ";
    zen::string z2 = "Trailing spaces   ";
    zen::string z3 = "No trailing spaces";
    zen::string z4 = "";
    zen::string z5 = "  ";

    // Test 1: Remove trailing spaces and tabs
    z1.rstrip();
    ZEN_EXPECT(z1 == "Hello, World!");

    // Test 2: Remove trailing spaces
    z2.rstrip();
    ZEN_EXPECT(z2 == "Trailing spaces");

    // Test 3: No trailing spaces to remove
    z3.rstrip();
    ZEN_EXPECT(z3 == "No trailing spaces");

    // Test 4: Empty string remains empty
    z4.rstrip();
    ZEN_EXPECT(z4.empty());

    // Test 5: Remove trailing spaces, leaving an empty string
    z5.rstrip();
    ZEN_EXPECT(z5.empty());
}

void test_string_lstrip() {
    zen::string z1 = "  \t  Hello, World!";
    zen::string z2 = "   Leading spaces";
    zen::string z3 = "No leading spaces";
    zen::string z4 = "";
    zen::string z5 = "  ";

    // Test 1: Remove leading spaces and tabs
    z1.lstrip();
    ZEN_EXPECT(z1 == "Hello, World!");

    // Test 2: Remove leading spaces
    z2.lstrip();
    ZEN_EXPECT(z2 == "Leading spaces");

    // Test 3: No leading spaces to remove
    z3.lstrip();
    ZEN_EXPECT(z3 == "No leading spaces");

    // Test 4: Empty string remains empty
    z4.lstrip();
    ZEN_EXPECT(z4.empty());

    // Test 5: Remove leading spaces, leaving an empty string
    z5.lstrip();
    ZEN_EXPECT(z5.empty());
}

void test_string_partition() {
    zen::string z1 = "apple;banana;cherry";
    std::string separator1 = ";";
    auto result1 = z1.partition(separator1);

    ZEN_EXPECT(std::get<0>(result1) == "apple");
    ZEN_EXPECT(std::get<1>(result1) == ";");
    ZEN_EXPECT(std::get<2>(result1) == "banana;cherry");

    zen::string z2 = "red,green,blue";
    std::string separator2 = ",";
    auto result2 = z2.partition(separator2);

    ZEN_EXPECT(std::get<0>(result2) == "red");
    ZEN_EXPECT(std::get<1>(result2) == ",");
    ZEN_EXPECT(std::get<2>(result2) == "green,blue");

    zen::string z3 = "one.two.three";
    std::string separator3 = ".";
    auto result3 = z3.partition(separator3);

    ZEN_EXPECT(std::get<0>(result3) == "one");
    ZEN_EXPECT(std::get<1>(result3) == ".");
    ZEN_EXPECT(std::get<2>(result3) == "two.three");

    zen::string z4 = "no_separator_here";
    std::string separator4 = ",";
    auto result4 = z4.partition(separator4);

    ZEN_EXPECT(std::get<0>(result4) == "no_separator_here");
    ZEN_EXPECT(std::get<1>(result4).empty());
    ZEN_EXPECT(std::get<2>(result4).empty());
}

void test_string_rpartition() {
    zen::string input1 = "apple;banana;cherry";
    zen::string separator1 = ";";

    auto result1 = input1.rpartition(separator1);

    ZEN_EXPECT(std::get<0>(result1) == "apple;banana");
    ZEN_EXPECT(std::get<1>(result1) == ";");
    ZEN_EXPECT(std::get<2>(result1) == "cherry");

    zen::string input2 = "one::two::three";
    zen::string separator2 = "::";

    auto result2 = input2.rpartition(separator2);

    ZEN_EXPECT(std::get<0>(result2) == "one::two");
    ZEN_EXPECT(std::get<1>(result2) == "::");
    ZEN_EXPECT(std::get<2>(result2) == "three");

    zen::string input3 = "no_separator_here";
    zen::string separator3 = "::";

    auto result3 = input3.rpartition(separator3);

    ZEN_EXPECT(std::get<0>(result3) == "no_separator_here");
    ZEN_EXPECT(std::get<1>(result3).empty());
    ZEN_EXPECT(std::get<2>(result3).empty());

    zen::string input4 = "::";
    zen::string separator4 = "::";

    auto result4 = input4.rpartition(separator4);

    ZEN_EXPECT(std::get<0>(result4).empty());
    ZEN_EXPECT(std::get<1>(result4) == "::");
    ZEN_EXPECT(std::get<2>(result4).empty());
}

void test_string_split() {
    zen::string input1 = "apple,banana,cherry";
    zen::string separator1 = ",";

    std::vector<zen::string> result1 = input1.split(separator1);

    ZEN_EXPECT(result1.size() == 3);
    ZEN_EXPECT(result1[0] == "apple");
    ZEN_EXPECT(result1[1] == "banana");
    ZEN_EXPECT(result1[2] == "cherry");

    zen::string input2 = "one|two|three|four";
    zen::string separator2 = "|";

    std::vector<zen::string> result2 = input2.split(separator2);

    ZEN_EXPECT(result2.size() == 4);
    ZEN_EXPECT(result2[0] == "one");
    ZEN_EXPECT(result2[1] == "two");
    ZEN_EXPECT(result2[2] == "three");
    ZEN_EXPECT(result2[3] == "four");

    zen::string input3 = "no_separator_here";
    zen::string separator3 = "|";

    std::vector<zen::string> result3 = input3.split(separator3);

    ZEN_EXPECT(result3.size() == 1);
    ZEN_EXPECT(result3[0] == "no_separator_here");

    zen::string input4 = "only_separator||||";
    zen::string separator4 = "|";

    std::vector<zen::string> result4 = input4.split(separator4);

    ZEN_EXPECT(result4.size() == 5);
    ZEN_EXPECT(result4[0] == "only_separator");
    ZEN_EXPECT(result4[1].empty());
    ZEN_EXPECT(result4[2].empty());
    ZEN_EXPECT(result4[3].empty());
    ZEN_EXPECT(result4[4].empty());

    zen::string input5 = "";
    zen::string separator5 = ",";

    std::vector<zen::string> result5 = input5.split(separator5);

    ZEN_EXPECT(result5.size() == 1);
    ZEN_EXPECT(result5[0].empty());
}

void main_test_string()
{
    BEGIN_TEST;

    std::string s = "[Hello World] 1.2.3";
    zen::string z = s; s = z; z = s; // check basic interchangability

    ZEN_EXPECT(z.contains("World"));
    ZEN_EXPECT(z.extract_between("[", "]").starts_with("Hello"));
    ZEN_EXPECT(z.extract_between("[", "]").ends_with(  "World"));

    // Check interchangeability with std::string // TODO: Cover more cases?
    std::string x = z; z = x;

    test_string_replace_all();
    test_string_substring();
    test_string_ends_with();
    test_string_pad_start();
    test_string_trimming();
    test_string_extract();
    test_string_pad_end();
    test_string_replace();
    test_string_remove();
    test_string_replace_if();
    test_string_replace_all_if();
    test_string_capitalize();
    test_string_to_lower();
    test_string_to_upper();
    test_string_center();
    test_string_is_alnum();
    test_string_is_alpha();
    test_string_is_decimal();
    test_string_is_digit();
    test_string_is_identifier();
    test_string_is_lower();
    test_string_is_upper();
    test_string_is_printable();
    test_string_is_space();
    test_string_ljust();
    test_string_rjust();
    test_string_rstrip();
    test_string_lstrip();
    test_string_partition();
    test_string_rpartition();
    test_string_split();

}
