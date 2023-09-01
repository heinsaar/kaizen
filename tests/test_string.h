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

    z = "Software Version 1.2.3";
    s = z.extract_pattern(R"((\d+\.\d+\.\d+))");
    assert(s == "1.2.3");

    z = "Some Date 1/2/2023";
    s = z.extract_pattern(R"((\d+\/\d+\/\d+))");
    assert(s == "1/2/2023");

    // Extract email address
    z = "Contact us at: support@example.com for more details.";
    s = z.extract_pattern(R"((\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b))");
    assert(s == "support@example.com");

    // Extract URL
    z = "Our website is http://www.example.com";
    s = z.extract_pattern(R"((https?://[^\s]+))");
    assert(s == "http://www.example.com");

    // Extract currency (price)
    z = "The cost is $25.99";
    s = z.extract_pattern(R"((\$\d+(\.\d{2})?))");
    assert(s == "$25.99");

    // Extract hashtags
    z = "Trending topics are #Tech #AI";
    s = z.extract_pattern(R"((#\w+))");
    assert(s == "#Tech"); // first hashtag
    
    // Extract file extension
    z = "The file is image.jpeg";
    s = z.extract_pattern(R"((\.\w+$))");
    assert(s == ".jpeg");

    // Trim a string from leading & trailing empty spaces
    z = "   No spaces    around me.  ";
    s = z.trim();
    assert(!::isspace(s.front()));
    assert(!::isspace(s.back()));

    zen::log(zen::color::green("TEST PASS:"), __func__);
}