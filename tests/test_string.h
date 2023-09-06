#pragma once

#include <cassert>
#include "../build/kaizen.h" // test using generated header

void sanitest_string()
{
    std::string s = "[Hello World] 1.2.3";
    zen::string z = s;

    // TODO: Find a better way than asserting: show red FAIL
    assert(z.contains("World"));
    assert(z.extract_between("[", "]").starts_with("Hello"));

    std::string x = z; z = x;

    // Extract software version
    z = "Software Version 1.2.3";
    s = z.extract_version();
    assert(s == "1.2.3");
    s = z.extract_pattern(R"((\d+\.\d+\.\d+))");
    assert(s == "1.2.3");

    // Extract date
    z = "Some Date 1/2/2023";
    s = z.extract_date();
    assert(s == "1/2/2023");
    s = z.extract_pattern(R"((\d+\/\d+\/\d+))");
    assert(s == "1/2/2023");

    // Extract email address
    z = "Contact us at: support@example.com for more details.";
    s = z.extract_email();
    assert(s == "support@example.com");
    s = z.extract_pattern(R"((\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b))");
    assert(s == "support@example.com");

    // Extract URL
    z = "Our website is http://www.example.com";
    s = z.extract_url();
    assert(s == "http://www.example.com");
    s = z.extract_pattern(R"((https?://[^\s]+))");
    assert(s == "http://www.example.com");

    // Extract currency (price)
    z = "The cost is $25.99";
    s = z.extract_pattern(R"((\$\d+(\.\d{2})?))");
    assert(s == "$25.99");

    // Extract hashtags
    z = "Trending topics are #Tech #AI";
    s = z.extract_hashtag();
    assert(s == "#Tech"); // first hashtag
    s = z.extract_pattern(R"((#\w+))");
    assert(s == "#Tech"); // first hashtag
    
    // Extract file extension
    z = "The file is image.jpeg";
    s = z.extract_extension();
    assert(s == ".jpeg");
    s = z.extract_pattern(R"((\.\w+$))");
    assert(s == ".jpeg");

    //   012345678912345 
    z = "Test substrings";
    assert(z.substring(  0,   4) == "Test");
    assert(z.substring( 10,   3) == "");           // from > to
    assert(z.substring(100, 300) == "");           // size() < from < to
    assert(z.substring(300, 100) == "");           // size() < to < from
    assert(z.substring(  5,   5) == "");           // empty string if indices are same
    assert(z.substring(-20,   4) == "Test");
    assert(z.substring(  0,  -5) == "Test subst");
    // Negative start, negative end
    assert(z.substring(-5,   -2) == "rin");
    assert(z.substring(-2,   -5) == "");           // unnatural edge case
    // Negative start, positive end
    assert(z.substring(-5,   24) == "rings");      // end out of bounds
    assert(z.substring(-24,   4) == "Test");
    // Positive start, negative end
    assert(z.substring(0,    -5) == "Test subst");
    assert(z.substring(30,   -5) == "");           // unnatural edge case
    // Out of bounds
    assert(z.substring( 25,  30) == "");           // both out of bounds
    assert(z.substring(-25, -30) == "");           // both out of bounds
    assert(z.substring(-30,   4) == "Test");       // start out of bounds
    // Various combinations
    assert(z.substring(-5,    5) == "");           // negative to positive that precedes it
    assert(z.substring( 5,   -5) == "subst");      // positive to negative that follows it
    // Full string           
    assert(z.substring(  0,  50) == "Test substrings");
    assert(z.substring(-30,  50) == "Test substrings");

    // Trim and deflate a string
    z = "   Trim   me  ";
    s = z.trim(); // from leading & trailing empty spaces
    assert(!::isspace(s.front()));
    assert(!::isspace(s.back()));
    assert(z.deflate().is_deflated());

    zen::log(zen::color::green("TEST PASS:"), __func__);
}