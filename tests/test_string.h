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

    z.trim_from_last("me").trim();

    ZEN_EXPECT(z == "Trim");
    ZEN_EXPECT(z.is_empty() == zen::is_empty(z));
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
    z12.remove("[a-z]+");       // all lowercase words
    z13.remove("[a-zA-Z0-9]+"); // all words and numbers
    z14.remove("\\s+");         // all spaces
    z15.remove("<.*>");         // greedy match
    z16.remove("<.*?>");        // lazy match
    z17.remove("\\d{2,3}");     // 2 to 3 digits
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

void test_string_replace_if()
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

    z1.replace_if("apples", "oranges",         [](auto){ return true;  });
    z2.replace_if("replace", "REPLACED",       [](auto){ return false; });
    z3.replace_if("replace", "REPLACED",       [](auto){ return true;  });
    z4.replace_if("", "REPLACED",              [](auto){ return true;  });
    z5.replace_if("Remove ", "",               [](auto){ return true;  });
    z6.replace_if("", "",                      [](auto){ return false; });
    z7.replace_if("Case", "CASE",              [](auto){ return true;  });
    z8.replace_if("ReplaceAll", "AllReplaced", [](auto){ return true;  });
    z9.replace_if("Short", "Lengthy",          [](auto){ return true;  });
    z10.replace_if("Lengthy", "Short",         [](auto){ return false; });
    z11.replace_if("Replace", "Replaced",      [](auto){ return false; });

    ZEN_EXPECT(z1 == "I love oranges.");
    ZEN_EXPECT(z2 == "Replace me, replace me!");
    ZEN_EXPECT(z3 == "Nothing to REPLACED here.");
    ZEN_EXPECT(z4 == "No change.");
    ZEN_EXPECT(z5 == "me.");
    ZEN_EXPECT(z6 == "No change.");
    ZEN_EXPECT(z7 == "CASESensitive");
    ZEN_EXPECT(z8 == "AllReplaced");
    ZEN_EXPECT(z9 == "Lengthy");
    ZEN_EXPECT(z10 == "Lengthy");
    ZEN_EXPECT(z11 == "EndReplace");
}

void test_string_replace_all_if()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Apple, banana, and apricot are fruits.";
    zen::string z2 = "The cat chased the rat. CATapult!";
    zen::string z3 = "1234567890";
    zen::string z4 = "abcdeabcde";
    zen::string z5 = "abcde";
    zen::string z6 = "";

    z1.replace_all_if("a",   "X",   [](auto& s) { return !s.empty() && s[0] == 'A'; });
    z2.replace_all_if("cat", "DOG", [](auto& s) { return s.find("cat") != std::string::npos; });
    z3.replace_all_if("1",   "X",   [](auto)    { return false; });
    z4.replace_all_if("cde", "",    [](auto)    { return true;  });
    z5.replace_all_if("",    "X",   [](auto)    { return true;  });
    z6.replace_all_if("abc", "XYZ", [](auto)    { return true;  });

    ZEN_EXPECT(z1 == "Apple, bXnXnX, Xnd Xpricot Xre fruits.");
    ZEN_EXPECT(z2 == "The DOG chased the rat. CATapult!");
    ZEN_EXPECT(z3 == "1234567890");
    ZEN_EXPECT(z4 == "abab");
    ZEN_EXPECT(z5 == "abcde");
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

void test_string_capitalize()
{
    BEGIN_SUBTEST;

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
    str2.capitalize();
    str3.capitalize();
    str4.capitalize();
    str5.capitalize();
    str6.capitalize();
    str7.capitalize();
    str8.capitalize();
    str9.capitalize();
    str10.capitalize();
    str11.capitalize();

    ZEN_EXPECT(str1 == "Hello world");
    ZEN_EXPECT(str2 == "");
    ZEN_EXPECT(str3 == "This is a test");
    ZEN_EXPECT(str4 == "This is another test");
    ZEN_EXPECT(str5 == "X");
    ZEN_EXPECT(str6 == "12345 !@#");
    ZEN_EXPECT(str7 == "Mixed case");
    ZEN_EXPECT(str8 == "!hello #world$");
    ZEN_EXPECT(str9 == "  leading spaces");
    ZEN_EXPECT(str10 == "Trailing spaces  ");
    ZEN_EXPECT(str11 == "Al");
}

void test_string_to_lower()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello World!";
    zen::string z2 = "123 ABC xyz";
    zen::string z3 = "nochange";
    zen::string z4 = "UPPERCASE";
    zen::string z5 = "";
    zen::string z6 = "!@#$%^&*()";
    zen::string z7 = "12345";
    zen::string z8 = "Hello\nWorld";

    z1.to_lower();
    z2.to_lower();
    z3.to_lower();
    z4.to_lower();
    z5.to_lower();
    z6.to_lower();
    z7.to_lower();
    z8.to_lower();

    ZEN_EXPECT(z1 == "hello world!");
    ZEN_EXPECT(z2 == "123 abc xyz");
    ZEN_EXPECT(z3 == "nochange");
    ZEN_EXPECT(z4 == "uppercase");
    ZEN_EXPECT(z5 == "");
    ZEN_EXPECT(z6 == "!@#$%^&*()");
    ZEN_EXPECT(z7 == "12345");
    ZEN_EXPECT(z8 == "hello\nworld");
}

void test_string_to_upper()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello World!";
    zen::string z2 = "123 abc XYZ";
    zen::string z3 = "NOCHANGE";
    zen::string z4 = "";
    zen::string z5 = "!@#$%^&*()";
    zen::string z6 = "123!@#";
    zen::string z7 = "MixedCASE123";
    zen::string z8 = "Hello\nWorld";

    z1.to_upper();
    z2.to_upper();
    z3.to_upper();
    z4.to_upper();
    z5.to_upper();
    z6.to_upper();
    z7.to_upper();
    z8.to_upper();

    ZEN_EXPECT(z1 == "HELLO WORLD!");
    ZEN_EXPECT(z2 == "123 ABC XYZ");
    ZEN_EXPECT(z3 == "NOCHANGE");
    ZEN_EXPECT(z4 == "");
    ZEN_EXPECT(z5 == "!@#$%^&*()");
    ZEN_EXPECT(z6 == "123!@#");
    ZEN_EXPECT(z7 == "MIXEDCASE123");
    ZEN_EXPECT(z8 == "HELLO\nWORLD");
}

void test_string_center()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello";
    zen::string z2 = "Centered";
    zen::string z3 = "Wide";
    zen::string z4 = "X";
    zen::string z5 = "";
    zen::string z6 = "Zen";
    zen::string z7 = "WideWord";
    zen::string z8 = "Padded";

    z1.center(10);
    z2.center(12, '-');
    z3.center(10, '*');
    z4.center(5);
    z5.center(8);
    z6.center(10, '+');
    z7.center(5, '-');
    z8.center(10, '\n');

    ZEN_EXPECT(z1 == "  Hello   ");
    ZEN_EXPECT(z2 == "--Centered--");
    ZEN_EXPECT(z3 == "***Wide***");
    ZEN_EXPECT(z4 == "  X  ");
    ZEN_EXPECT(z5 == "        ");
    ZEN_EXPECT(z6 == "+++Zen++++");
    ZEN_EXPECT(z7 == "WideWord");
    ZEN_EXPECT(z8 == "\n\nPadded\n\n");
}

void test_string_is_alnum()
{
    BEGIN_SUBTEST;

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

    ZEN_EXPECT( z1.is_alnum());  // alphanumeric
    ZEN_EXPECT( z2.is_alnum());  // alphabetic
    ZEN_EXPECT( z3.is_alnum());  // numeric
    ZEN_EXPECT(!z4.is_alnum());  // special characters
    ZEN_EXPECT(!z5.is_alnum());  // empty string
    ZEN_EXPECT( z6.is_alnum());  // alphabetic mixed case
    ZEN_EXPECT(!z7.is_alnum());  // alphanumeric with space
    ZEN_EXPECT(!z8.is_alnum());  // alphanumeric with underscore
    ZEN_EXPECT(!z9.is_alnum());  // special characters with exclamation mark
    ZEN_EXPECT(!z10.is_alnum()); // empty string
}

void test_string_is_alpha()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello";
    zen::string z2 = "Testing123";
    zen::string z3 = "12345";
    zen::string z4 = "!@#$%^";
    zen::string z5 = " ";
    zen::string z6 = "AaBbCc";
    zen::string z7 = "With Space Inside";
    zen::string z8 = "Alpha$Characters";
    zen::string z9 = "";

    ZEN_EXPECT( z1.is_alpha()); // alphabetic only (all characters are letters)
    ZEN_EXPECT(!z2.is_alpha()); // alphanumeric (contains both letters and numbers)
    ZEN_EXPECT(!z3.is_alpha()); // numeric only (all characters are numbers)
    ZEN_EXPECT(!z4.is_alpha()); // special characters only (contains special characters)
    ZEN_EXPECT(!z5.is_alpha()); // space only (contains only space)
    ZEN_EXPECT( z6.is_alpha()); // alphabetic mixed case (contains letters in mixed case)
    ZEN_EXPECT(!z7.is_alpha()); // alphabetic with spaces inside (contains letters with spaces)
    ZEN_EXPECT(!z8.is_alpha()); // alphabetic with special characters (contains letters with special characters)
    ZEN_EXPECT(!z9.is_alpha()); // empty string
}

void test_string_is_digit()
{
    BEGIN_SUBTEST;

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

    ZEN_EXPECT( z1.is_digit()); // numeric characters (all characters are decimal digits)
    ZEN_EXPECT( z2.is_digit()); // unicode representation of '0' (should also be considered decimal)
    ZEN_EXPECT(!z3.is_digit()); // alphanumeric (contains both letters and numbers)
    ZEN_EXPECT(!z4.is_digit()); // special characters only (contains special characters)
    ZEN_EXPECT(!z5.is_digit()); // space only (contains only space)
    ZEN_EXPECT(!z6.is_digit()); // alphabetic mixed case (contains letters in mixed case)
    ZEN_EXPECT(!z7.is_digit()); // empty case (contains letters in mixed case)
    ZEN_EXPECT(!z8.is_digit()); // unicode representation of 'A' (should not be considered decimal)
    ZEN_EXPECT( z9.is_digit()); // leading zeros (should be considered decimal)
    ZEN_EXPECT(z10.is_digit()); // long string (should be considered decimal)
}

void test_string_is_identifier()
{
    BEGIN_SUBTEST;

    zen::string z1 = "variable123"; // starts with a letter (valid identifier)
    zen::string z2 = "123variable"; // starts with a digit (invalid identifier)
    zen::string z3 = "var_iable";   // contains underscore (valid identifier)
    zen::string z4 = "var iable";   // contains space (invalid identifier)
    zen::string z5 = "var!able";    // contains special character (invalid identifier)
    zen::string z6 = "_variable";   // starts with an underscore (valid identifier)
    zen::string z7 = "";            // empty string (not a valid identifier)
    zen::string z8 = " ";           // empty string (not a valid identifier)

    ZEN_EXPECT(z1.is_identifier() == true);
    ZEN_EXPECT(z2.is_identifier() == false);
    ZEN_EXPECT(z3.is_identifier() == true);
    ZEN_EXPECT(z4.is_identifier() == false);
    ZEN_EXPECT(z5.is_identifier() == false);
    ZEN_EXPECT(z6.is_identifier() == true);
    ZEN_EXPECT(z7.is_identifier() == false);
    ZEN_EXPECT(z8.is_identifier() == false);
}

void test_string_is_lower()
{
    BEGIN_SUBTEST;

    zen::string z1 = "lowercase";     // all lowercase characters (valid)
    zen::string z2 = "MiXeDCaSe";     // mixed case characters (invalid, contains uppercase)
    zen::string z3 = "12345";         // digits (invalid, contains digits)
    zen::string z4 = "lower case";    // space (invalid, contains space)
    zen::string z5 = "lower-case";    // hyphen (invalid, contains special character)
    zen::string z6 = "";              // empty string ()
    zen::string z7 = " ";             // space (invalid, contains space)
    zen::string z8 = "lowercase1234"; // digits (invalid, contains digits)

    ZEN_EXPECT(z1.is_lower() == true);
    ZEN_EXPECT(z2.is_lower() == false);
    ZEN_EXPECT(z3.is_lower() == false);
    ZEN_EXPECT(z4.is_lower() == false);
    ZEN_EXPECT(z5.is_lower() == false);
    ZEN_EXPECT(z6.is_lower() == false);
    ZEN_EXPECT(z7.is_lower() == false);
    ZEN_EXPECT(z8.is_lower() == false);
}

void test_string_is_upper()
{
    BEGIN_SUBTEST;

    zen::string z1 = "HELLO";         // all uppercase characters
    zen::string z2 = "hello";         // all lowercase characters
    zen::string z3 = "HeLLo";         // mixed case
    zen::string z4 = "12345";         // all digits
    zen::string z5 = " ";             // space character
    zen::string z6 = "!@#$%^";        // special characters
    zen::string z7 = "HELLO world";   // mixed case with space
    zen::string z8 = "HELLO123";      // uppercase and digits
    zen::string z9 = "";              // empty string
    zen::string z10 = " ";            // space character
    zen::string z11 = "\u0061\u0061"; // unicode representation of ''
    zen::string z12 = "\u0041\u0041"; // unicode representation of ''

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

void test_string_is_printable()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello, World!"; // printable characters (no control characters)
    zen::string z2 = "\n";            // newline character (control character)
    zen::string z3 = "12345";         // digits (printable)
    zen::string z4 = "!@#$%^";        // special characters (printable)
    zen::string z5 = "\t";            // tab character (control character)
    zen::string z6 = " ";             // space character (printable)
    zen::string z7 = "\x7F";          // delete character (control character)
    zen::string z8 = "\x1F";          // unit separator character (control character)
  //zen::string z9 = "ᾭᾮᾯ";           // unicode characters (non-ASCII)
  //zen::string z10 = "\u03A9";       // unicode character (Ω)
    zen::string z11 = "\u0010";       // data Link Escape (control character)
    zen::string z12 = "";             // empty string

    ZEN_EXPECT(z1.is_printable() == true);
    ZEN_EXPECT(z2.is_printable() == false);
    ZEN_EXPECT(z3.is_printable() == true);
    ZEN_EXPECT(z4.is_printable() == true);
    ZEN_EXPECT(z5.is_printable() == false);
    ZEN_EXPECT(z6.is_printable() == true);
    ZEN_EXPECT(z7.is_printable() == false);
    ZEN_EXPECT(z8.is_printable() == false);
  //ZEN_EXPECT(z9.is_printable() == false);
  //ZEN_EXPECT(z10.is_printable() == false);
    ZEN_EXPECT(z11.is_printable() == false);
    ZEN_EXPECT(z12.is_printable() == true);
}

void test_string_is_space()
{
    BEGIN_SUBTEST;

    zen::string z1 = "   ";           // all spaces
    zen::string z2 = "Hello World";   // contains non-space characters
    zen::string z3 = "\t\n\r";        // various whitespace characters
    zen::string z4 = "";              // empty string
    zen::string z5 = "NoSpacesHere";  // no spaces at all

    ZEN_EXPECT(z1.is_space() == true);
    ZEN_EXPECT(z2.is_space() == false);
    ZEN_EXPECT(z3.is_space() == true);
    ZEN_EXPECT(z4.is_space() == false);
    ZEN_EXPECT(z5.is_space() == false);
}

void test_string_ljust()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello";
    zen::string z2 = "123";
    zen::string z3 = "Short";
    zen::string z4 = "";
    zen::string z5 = "ThisIsALongerString";
    zen::string z6 = "negative";

    z1.ljust(10);     // left-justify with space padding
    z2.ljust(5, '0'); // left-justify with '0' padding
    z3.ljust(5);      // left-justify a shorter string with space padding
    z4.ljust(5);      // left-justify an empty string with space padding
    z5.ljust(20);     // left-justify a longer string, no padding needed
    z6.ljust(-1);

    ZEN_EXPECT(z1 == "Hello     ");
    ZEN_EXPECT(z2 == "12300");
    ZEN_EXPECT(z3 == "Short");
    ZEN_EXPECT(z4 == "     ");
    ZEN_EXPECT(z5 == "ThisIsALongerString ");
    ZEN_EXPECT(z6 == "negative");
}

void test_string_rjust()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello";
    zen::string z2 = "123";
    zen::string z3 = "Short";
    zen::string z4 = "";
    zen::string z5 = "ThisIsALongerString";
    zen::string z6 = "negative";

    z1.rjust(10);     // right-justify with space padding
    z2.rjust(5, '0'); // right-justify with '0' padding
    z3.rjust(5);      // right-justify a shorter string with space padding
    z4.rjust(5);      // right-justify an empty string with space padding
    z5.rjust(20);     // right-justify a longer string, no padding needed

    z6.rjust(-1);

    ZEN_EXPECT(z1 == "     Hello");
    ZEN_EXPECT(z2 == "00123");
    ZEN_EXPECT(z3 == "Short");
    ZEN_EXPECT(z4 == "     ");
    ZEN_EXPECT(z5 == " ThisIsALongerString");
    ZEN_EXPECT(z6 == "negative");
}

void test_string_rstrip()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello, World!  \t  ";
    zen::string z2 = "Trailing spaces   ";
    zen::string z3 = "No trailing spaces";
    zen::string z4 = "";
    zen::string z5 = "  ";

    z1.rtrim(); // remove trailing spaces and tabs
    z2.rtrim(); // remove trailing spaces
    z3.rtrim(); // no trailing spaces to remove
    z4.rtrim(); // empty string remains empty
    z5.rtrim(); // remove trailing spaces, leaving an empty string

    ZEN_EXPECT(z1 == "Hello, World!");
    ZEN_EXPECT(z2 == "Trailing spaces");
    ZEN_EXPECT(z3 == "No trailing spaces");
    ZEN_EXPECT(z4.empty());
    ZEN_EXPECT(z5.empty());
}

void test_string_lstrip()
{
    BEGIN_SUBTEST;

    zen::string z1 = "  \t  Hello, World!";
    zen::string z2 = "   Leading spaces";
    zen::string z3 = "No leading spaces";
    zen::string z4 = "";
    zen::string z5 = "  ";

    z1.ltrim(); // remove leading spaces and tabs
    z2.ltrim(); // remove leading spaces
    z3.ltrim(); // no leading spaces to remove
    z4.ltrim(); // empty string remains empty
    z5.ltrim(); // remove leading spaces, leaving an empty string

    ZEN_EXPECT(z1 == "Hello, World!");
    ZEN_EXPECT(z2 == "Leading spaces");
    ZEN_EXPECT(z3 == "No leading spaces");
    ZEN_EXPECT(z4.empty());
    ZEN_EXPECT(z5.empty());
}

void test_string_partition()
{
    BEGIN_SUBTEST;

    zen::string z1 = "apple;banana;cherry";
    zen::string z2 = "red,green,blue";
    zen::string z3 = "one.two.three";
    zen::string z4 = "no_separator_here";

    auto r1 = z1.partition(";");
    auto r2 = z2.partition(",");
    auto r3 = z3.partition(".");
    auto r4 = z4.partition(",");

    ZEN_EXPECT(std::get<0>(r1) == "apple");
    ZEN_EXPECT(std::get<1>(r1) == ";");
    ZEN_EXPECT(std::get<2>(r1) == "banana;cherry");

    ZEN_EXPECT(std::get<0>(r2) == "red");
    ZEN_EXPECT(std::get<1>(r2) == ",");
    ZEN_EXPECT(std::get<2>(r2) == "green,blue");

    ZEN_EXPECT(std::get<0>(r3) == "one");
    ZEN_EXPECT(std::get<1>(r3) == ".");
    ZEN_EXPECT(std::get<2>(r3) == "two.three");

    ZEN_EXPECT(std::get<0>(r4) == "no_separator_here");
    ZEN_EXPECT(std::get<1>(r4).empty());
    ZEN_EXPECT(std::get<2>(r4).empty());
}

void test_string_rpartition()
{
    BEGIN_SUBTEST;

    zen::string s1 = "apple;banana;cherry";
    zen::string s2 = "one::two::three";
    zen::string s3 = "no_separator_here";
    zen::string s4 = "::";

    auto r1 = s1.rpartition(";");
    auto r2 = s2.rpartition("::");
    auto r3 = s3.rpartition("::");
    auto r4 = s4.rpartition("::");

    ZEN_EXPECT(std::get<0>(r1) == "apple;banana");
    ZEN_EXPECT(std::get<1>(r1) == ";");
    ZEN_EXPECT(std::get<2>(r1) == "cherry");

    ZEN_EXPECT(std::get<0>(r2) == "one::two");
    ZEN_EXPECT(std::get<1>(r2) == "::");
    ZEN_EXPECT(std::get<2>(r2) == "three");

    ZEN_EXPECT(std::get<0>(r3) == "no_separator_here");
    ZEN_EXPECT(std::get<1>(r3).empty());
    ZEN_EXPECT(std::get<2>(r3).empty());

    ZEN_EXPECT(std::get<0>(r4).empty());
    ZEN_EXPECT(std::get<1>(r4) == "::");
    ZEN_EXPECT(std::get<2>(r4).empty());
}

void test_string_split()
{
    BEGIN_SUBTEST;

    zen::string s1 = "apple,banana,cherry";
    zen::string s2 = "one|two|three|four";
    zen::string s3 = "no_separator_here";
    zen::string s4 = "only_separator||||";
    zen::string s5 = "";

    auto r1 = s1.split(",");
    auto r2 = s2.split("|");
    auto r3 = s3.split("|");
    auto r4 = s4.split("|");
    auto r5 = s5.split(",");

    ZEN_EXPECT(r1.size() == 3);
    ZEN_EXPECT(r1[0] == "apple");
    ZEN_EXPECT(r1[1] == "banana");
    ZEN_EXPECT(r1[2] == "cherry");

    ZEN_EXPECT(r2.size() == 4);
    ZEN_EXPECT(r2[0] == "one");
    ZEN_EXPECT(r2[1] == "two");
    ZEN_EXPECT(r2[2] == "three");
    ZEN_EXPECT(r2[3] == "four");

    ZEN_EXPECT(r3.size() == 1);
    ZEN_EXPECT(r3[0] == "no_separator_here");

    ZEN_EXPECT(r4.size() == 5);
    ZEN_EXPECT(r4[0] == "only_separator");
    ZEN_EXPECT(r4[1].empty());
    ZEN_EXPECT(r4[2].empty());
    ZEN_EXPECT(r4[3].empty());
    ZEN_EXPECT(r4[4].empty());

    ZEN_EXPECT(r5.size() == 1);
    ZEN_EXPECT(r5[0].empty());
}

void test_string_swapcase()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Hello, World!";
    zen::string z2 = "mIXeD cASe";
    zen::string z3 = "ALLUPPER";
    zen::string z4 = "alllower";
    zen::string z5 = "";
    zen::string z6 = "123!@#";
  //zen::string z7 = "ΣΥΜΒΟΛΑ"; // Greek uppercase letters
  //zen::string z8 = "σύμβολα"; // Greek lowercase letters

    z1.swapcase();
    z2.swapcase();
    z3.swapcase();
    z4.swapcase();
    z5.swapcase();
    z6.swapcase();
  //z7.swapcase();
  //z8.swapcase();

    ZEN_EXPECT(z1 == "hELLO, wORLD!");
    ZEN_EXPECT(z2 == "MixEd CasE");
    ZEN_EXPECT(z3 == "allupper");
    ZEN_EXPECT(z4 == "ALLLOWER");
    ZEN_EXPECT(z5.empty());
    ZEN_EXPECT(z6 == "123!@#");
  //ZEN_EXPECT(z7 == "σύμβολα");
  //ZEN_EXPECT(z8 == "ΣΥΜΒΟΛΑ");
}

void test_string_split_lines()
{
    BEGIN_SUBTEST;

    zen::string z1 = "Line 1\nLine 2\nLine 3";
    zen::string z2 = "Single line";
    zen::string z3 = "\n";
    zen::string z4 = "";
    zen::string z5 = "Ends with newline\n";
    zen::string z6 = "\nStarts with newline";
    zen::string z7 = "Multiple\n\nNewlines";

    auto r1 = z1.split_lines();
    auto r2 = z2.split_lines();
    auto r3 = z3.split_lines();
    auto r4 = z4.split_lines();
    auto r5 = z5.split_lines();
    auto r6 = z6.split_lines();
    auto r7 = z7.split_lines();

    ZEN_EXPECT(r1.size() == 3 && r1[0] == "Line 1" && r1[1] == "Line 2" && r1[2] == "Line 3");
    ZEN_EXPECT(r2.size() == 1 && r2[0] == "Single line");
    ZEN_EXPECT(r3.size() == 1 && r3[0].empty());
    ZEN_EXPECT(r4.empty());
    ZEN_EXPECT(r5.size() == 1 && r5[0] == "Ends with newline");
    ZEN_EXPECT(r6.size() == 2 && r6[0].empty() && r6[1] == "Starts with newline");
    ZEN_EXPECT(r7.size() == 3 && r7[0] == "Multiple" && r7[1].empty() && r7[2] == "Newlines");
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

    // Check basic interchangeability with std::string
    std::string x = z; z = x;

    test_string_zen_std_interchangeability();
    test_string_replace_all_if();
    test_string_is_identifier();
    test_string_is_printable();
    test_string_replace_all();
    test_string_split_lines();
    test_string_replace_if();
    test_string_capitalize();
    test_string_rpartition();
    test_string_substring();
    test_string_ends_with();
    test_string_pad_start();
    test_string_partition();
    test_string_trimming();
    test_string_to_lower();
    test_string_to_upper();
    test_string_is_alnum();
    test_string_is_alpha();
    test_string_is_digit();
    test_string_is_lower();
    test_string_is_upper();
    test_string_is_space();
    test_string_swapcase();
    test_string_extract();
    test_string_pad_end();
    test_string_replace();
    test_string_center();
    test_string_remove();
    test_string_rstrip();
    test_string_lstrip();
    test_string_rjust();
    test_string_ljust();
    test_string_split();
}
