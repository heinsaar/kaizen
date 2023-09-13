#pragma once

#include "kaizen.h" // test using generated header: jump with the parachute you folded

void test_string_extract()
{
    BEGIN_SUBTEST;

    zen::string z = "[Hello World] 1.2.3";

    ZEN_EXPECT(z.contains("World"));
    ZEN_EXPECT(z.extract_between("[", "]").starts_with("Hello"));

    // Extract software version
    z = "Software Version 1.2.3.4";
    std::string s = z.extract_version();
    ZEN_EXPECT(s == "1.2.3.4");
    s = z.extract_pattern(R"((\d+\.\d+\.\d+))");
    ZEN_EXPECT(s == "1.2.3");

    // Extract date
    z = "Some Date 1/2/2023";
    s = z.extract_date();
    ZEN_EXPECT(s == "1/2/2023");
    s = z.extract_pattern(R"((\d+\/\d+\/\d+))");
    ZEN_EXPECT(s == "1/2/2023");

    // Extract email address
    z = "Contact us at: support@example.com for more details.";
    s = z.extract_email();
    ZEN_EXPECT(s == "support@example.com");
    s = z.extract_pattern(R"((\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b))");
    ZEN_EXPECT(s == "support@example.com");

    // Extract URL
    z = "Our website is http://www.example.com";
    s = z.extract_url();
    ZEN_EXPECT(s == "http://www.example.com");
    s = z.extract_pattern(R"((https?://[^\s]+))");
    ZEN_EXPECT(s == "http://www.example.com");

    // Extract currency (price)
    z = "The cost is $25.99";
    s = z.extract_pattern(R"((\$\d+(\.\d{2})?))");
    ZEN_EXPECT(s == "$25.99");

    // Extract hashtags
    z = "Trending topics are #Tech #AI";
    s = z.extract_hashtag();
    ZEN_EXPECT(s == "#Tech"); // first hashtag
    s = z.extract_pattern(R"((#\w+))");
    ZEN_EXPECT(s == "#Tech"); // first hashtag
    
    // Extract file extension
    z = "The file is image.jpeg";
    s = z.extract_extension();
    ZEN_EXPECT(s == ".jpeg");
    s = z.extract_pattern(R"((\.\w+$))");
    ZEN_EXPECT(s == ".jpeg");
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
    ZEN_EXPECT(!::isspace(s.front()));
    ZEN_EXPECT(!::isspace(s.back()));
    ZEN_EXPECT(z.deflate().is_deflated());
    ZEN_EXPECT(z.is_empty() == zen::is_empty(z));

    ZEN_EXPECT(zen::replicate("*", 10) == "**********");
    ZEN_EXPECT(zen::replicate(10, "*") == "**********");

}

void test_string_remove()
{
    BEGIN_SUBTEST;

    zen::string str1 = "Hello, world!";     // basic
    str1.remove("world");
    ZEN_EXPECT(str1 == "Hello, !");

    zen::string str2 = "world world world"; // multiple occurrences
    str2.remove("world");
    ZEN_EXPECT(str2 == "  ");

    zen::string str3 = "Hello, WORLD!";     // case sensitivity
    str3.remove("world");
    ZEN_EXPECT(str3 == "Hello, WORLD!");

    zen::string str4 = "Hello, world!";     // no occurrences
    str4.remove("earth");
    ZEN_EXPECT(str4 == "Hello, world!");

    zen::string str5 = "Hello  world!";     // remove spaces
    str5.remove("  ");
    ZEN_EXPECT(str5 == "Helloworld!");

    zen::string str6 = "";                  // empty string
    str6.remove("world");
    ZEN_EXPECT(str6 == "");

    zen::string str7 = "world";             // remove entire string
    str7.remove("world");
    ZEN_EXPECT(str7 == "");

    zen::string str8 = "Hello, world! Have a good world!";
    str8.remove("world");
    ZEN_EXPECT(str8 == "Hello, ! Have a good !");   // pattern 'world' should be removed

    zen::string str9 = "123 123 123";
    str9.remove("\\d+");
    ZEN_EXPECT(str9 == "  ");                       // pattern '\\d+' should remove all digits

    zen::string str10 = "aaabbaaa";
    str10.remove("a*");
    ZEN_EXPECT(str10 == "bb");                      // pattern 'a*' should remove all 'a'

    zen::string str12 = "Hello, world! 123";
    str12.remove("[a-z]+");                         // all lowercase words
    ZEN_EXPECT(str12 == "H, ! 123");                // pattern '[a-z]+' should remove all lowercase words

    zen::string str13 = "Hello, world! 123";
    str13.remove("[a-zA-Z0-9]+");                   // all words and numbers
    ZEN_EXPECT(str13 == ", ! ");                    // pattern '[a-zA-Z0-9]+' should remove all words and numbers

    zen::string str14 = "  extra  spaces  ";
    str14.remove("\\s+");                           // all spaces
    ZEN_EXPECT(str14 == "extraspaces");             // pattern '\\s+' should remove all extra spaces

    zen::string str15 = "<tag>content</tag>";
    str15.remove("<.*>");                           // greedy match
    ZEN_EXPECT(str15 == "");                        // pattern '<.*>' should remove everything

    zen::string str16 = "<tag>content</tag>";
    str16.remove("<.*?>");                          // lazy match
    ZEN_EXPECT(str16 == "content");                 // pattern '<.*?>' should remove all tags but leave content

    zen::string str17 = "Hello123World";
    str17.remove("\\d{2,3}");                      // 2 to 3 digits
    ZEN_EXPECT(str17 == "HelloWorld");             // pattern '\\d{2,3}' should remove 123
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

    test_string_substring();
    test_string_ends_with();
    test_string_trimming();
    test_string_extract();
    test_string_remove();
}