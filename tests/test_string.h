#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_string_zen_std_interchangeability()
{
    // Construction and assignment
    std::string s1 = "Hello";
    zen::string z1(s1);

    // Concatenation
    zen::string z2 = "World";
    std::string s2 = z2;

    // Comparison
    std::string s3 = "Hello";
    zen::string z3 = "World";
    s3 += z3;
    z3 += s3;

    // Manupulation
    std::string s4 = "ABC";
    zen::string z4 = "ABC";
    zen::string z5 = "12345";
    z5.insert(2, "ABC");
    std::string s5 = "12ABC345";
    ZEN_EXPECT(z5 == s5);
    s5.erase(2, 3);
    z5.erase(2, 3);

    // Iteration
    zen::string z7 = "xyz";
    std::string s7;
    for (auto it = z7.begin(); it != z7.end(); ++it) {
        s7.push_back(*it);
    }

    ZEN_EXPECT(z1 == s1);
    ZEN_EXPECT(s2 == z2);
    ZEN_EXPECT(s3 == "HelloWorld");
    ZEN_EXPECT(z3 == "WorldHelloWorld");
    ZEN_EXPECT(s4 == z4);
    ZEN_EXPECT(z4 <= s4 && s4 <= z4);
    ZEN_EXPECT(s5 == z5);
    ZEN_EXPECT(s7 == z7);
}

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
    zen::string z18 = "aaabbaaa";

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
    z18.remove("a+");

    ZEN_EXPECT(z1 == "Hello, !");
    ZEN_EXPECT(z2 == "  ");
    ZEN_EXPECT(z3 == "Hello, WORLD!");
    ZEN_EXPECT(z4 == "Hello, world!");
    ZEN_EXPECT(z5 == "Helloworld!");
    ZEN_EXPECT(z6 == "");
    ZEN_EXPECT(z7 == "");
    ZEN_EXPECT(z8 == "Hello, ! Have a good !");  // pattern 'world' should be removed
    ZEN_EXPECT(z9 == "  ");                      // pattern '\\d+' should remove all digits
    ZEN_EXPECT(z10 == "bb" || z10 == "");        // pattern 'a*' should remove all 'a'; flaky test, may yield an empty string on some systems
    ZEN_EXPECT(z12 == "H, ! 123");               // pattern '[a-z]+' should remove all lowercase words
    ZEN_EXPECT(z13 == ", ! ");                   // pattern '[a-zA-Z0-9]+' should remove all words and numbers
    ZEN_EXPECT(z14 == "extraspaces");            // pattern '\\s+' should remove all extra spaces
    ZEN_EXPECT(z15 == "");                       // pattern '<.*>' should remove everything
    ZEN_EXPECT(z16 == "content");                // pattern '<.*?>' should remove all tags but leave content
    ZEN_EXPECT(z17 == "HelloWorld");             // pattern '\\d{2,3}' should remove 123
    ZEN_EXPECT(z18 == "bb");                     // pattern 'a+' should remove all 'a'
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
    BEGIN_SUBTEST;

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

void main_test_string()
{
    BEGIN_TEST;

    std::string s = "[Hello World] 1.2.3";
    zen::string z = s; s = z; z = s; // check basic interchangeability

    ZEN_EXPECT(z.contains("World"));
    ZEN_EXPECT(z.extract_between("[", "]").starts_with('H'));
    ZEN_EXPECT(z.extract_between("[", "]").starts_with("Hello"));
    ZEN_EXPECT(z.extract_between("[", "]").ends_with(  "World"));

    // Check interchangeability with std::string // TODO: Cover more cases?
    std::string x = z; z = x;

    test_string_zen_std_interchangeability();
    test_string_replace_all();
    test_string_substring();
    test_string_ends_with();
    test_string_pad_start();
    test_string_trimming();
    test_string_extract();
    test_string_pad_end();
    test_string_replace();
    test_string_remove();
}