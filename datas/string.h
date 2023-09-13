// MIT License
// 
// Copyright (c) 2023 Leo Heinsaar
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <algorithm>
#include <string>
#include <regex>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::string

struct string : std::string // read 'struct' as "extend the interface"
{
    using std::string::string;    // inherit constructors, has to be explicit
    using std::string::operator=; // inherit assignment operators, has to be explicit

    string(const std::string&     s) : std::string(s) {}
    string(const std::string_view s) : std::string(s) {}

    // Non-modifying functions
    bool starts_with(const std::string_view s) const { return substr(0, s.length()) == s; }
    bool ends_with(  const std::string_view s) const {
        if (size() < s.size()) return false;
        return substr(size() - s.size(), s.size()) == s;
    }
    
#if __cplusplus < 202303L // check pre-C++23, at which point std::string::contains() is standard
    // SFINAE to ensure that this version is only enabled when Pred is callable
    template<class Pred, typename = std::enable_if_t<std::is_invocable_r_v<bool, Pred, char>>>
    bool contains(const Pred& p)            const { return std::find_if(my::begin(), my::end(), p) != my::end(); }
    bool contains(const std::string_view s) const { return find(s) != std::string::npos; }
#endif

    bool is_empty() const { return my::empty(); }

    // For some string s = "[EXTRACTME]"; 
    // ......................^^^^^^^^^...
    // Usage: s.extract_between("[", "]");
    zen::string extract_between(const std::string_view beg, const std::string_view end) const
    {
        const size_t posBeg = find(beg);
        if (posBeg == std::string::npos)
            return ""; // signals 'not found'
        const size_t posEnd = find(end, posBeg + 1);
        if (posEnd == std::string::npos)
            return ""; // signals 'not found'
        return substr(posBeg + 1, posEnd - posBeg - 1);
    }

    // TODO: Maybe replace the std::string argument with std::regex here?
    zen::string extract_pattern(const std::string& pattern) {
        const std::regex regex_pattern(pattern);
        std::smatch match;
        std::string in(my::begin(), my::end());

        if (std::regex_search(in,   match, regex_pattern)) {
            const size_t startPos = match.position(0);
            const size_t length   = match.length(0);

            // Create a sub-string_view using the position and length
            return std::string(my::data() + startPos, length);
        }

        return ""; // signals 'no match'
    }

    // TODO: Maybe replace the std::string argument with std::regex here?
    zen::string& remove(const std::string& pattern)
    {
        // Use regex_replace to remove all occurrences of the pattern
        *this = std::regex_replace(*this, std::regex(pattern), std::string(""));
        return *this; // for natural chaining
    }

    auto extract_version()   { return extract_pattern(R"((\d+)\.(\d+)\.(\d+)\.(\d+))"                          ); } // Like "X.Y.Z.B"
    auto extract_date()      { return extract_pattern(R"((\d+\/\d+\/\d+))"                                     ); } // Like "31/12/2021"
    auto extract_email()     { return extract_pattern(R"((\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b))"); }
    auto extract_url()       { return extract_pattern(R"((https?://[^\s]+))"                                   ); }
    auto extract_hashtag()   { return extract_pattern(R"((#\w+))"                                              ); } // Like "#event"
    auto extract_extension() { return extract_pattern(R"((\.\w+$))"                                            ); }

    // Modifying functions
    auto& prefix(const std::string_view s)
    {
        insert(0, s);
        return *this;
    }

    auto& replace_all(const std::string_view oldStr, const std::string_view newStr)
    {
        size_t startPos = 0;
        while ((startPos = find(oldStr, startPos)) != std::string::npos) {
            replace(startPos, oldStr.length(), newStr);
            startPos += newStr.length(); // handles the case of 'newStr' being a substring of 'oldStr'
        }
        return *this;
    }

    auto& trim_from_last(const std::string_view str)
    {
        *this = substr(0, rfind(str));
        return *this;
    }

    auto& trim()
    {
        // Trim leading and trailing spaces
        my::assign(std::regex_replace(*this, std::regex("^\\s+|\\s+$"), std::string("")));
        return *this; // for natural chaining
    }

    auto& deflate()
    {
        // Replace any & all multiple spaces with a single space
        my::assign(std::regex_replace(my::trim(), std::regex("\\s+"), " "));
        return *this; // for natural chaining
    }

    bool is_deflated() const
    {
        auto neighbor_spaces = [](char a, char b) { return std::isspace(a) && std::isspace(b); };
        return my::end() == std::adjacent_find(my::begin(), my::end(), neighbor_spaces);
    }

    auto substring(int i1, int i2) const {
        const int sz = static_cast<int>(size());

        // Convert negative indices to positive, if necessary
        if (i1 < 0) i1 += sz;
        if (i2 < 0) i2 += sz;

        // Clamp indices to valid range
        i1 = std::clamp<int>(i1, 0, sz);
        i2 = std::clamp<int>(i2, 0, sz);

        if (i2 <= i1) {
            return zen::string(""); // empty string signals a negative result and is harmless
        }

        return zen::string(substr(i1, i2 - i1));
    }

    // TODO: Implement these (from Python string)
    // capitalize()	    Converts the first character to upper case
    // to_lower()	    Converts string into lower case
    // center()	        Returns a centered string
    // is_alnum()	    Returns True if all characters in the string are alphanumeric
    // is_alpha()	    Returns True if all characters in the string are in the alphabet
    // is_ascii()	    Returns True if all characters in the string are ascii characters
    // is_decimal()	    Returns True if all characters in the string are decimals
    // is_digit()	    Returns True if all characters in the string are digits
    // is_identifier()	Returns True if the string is an identifier
    // is_lower()	    Returns True if all characters in the string are lower case
    // is_numeric()	    Returns True if all characters in the string are numeric
    // is_printable()	Returns True if all characters in the string are printable
    // is_space()	    Returns True if all characters in the string are whitespaces
    // is_upper()	    Returns True if all characters in the string are upper case
    // ljust()	        Returns a left justified version of the string
    // lstrip()	        Returns a left trim version of the string
    // partition()	    Returns a tuple where the string is parted into three parts
    // rfind()	        Searches the string for a specified value and returns the last position of where it was found
    // rjust()	        Returns a right justified version of the string
    // rpartition()	    Returns a tuple where the string is parted into three parts
    // rsplit()	        Splits the string at the specified separator, and returns a list
    // rstrip()	        Returns a right trim version of the string
    // split()	        Splits the string at the specified separator, and returns a list
    // split_lines()	Splits the string at line breaks and returns a list
    // strip()	        Returns a trimmed version of the string
    // swapcase()	    Swaps cases, lower case becomes upper case and vice versa
    // to_upper()	    Converts a string into upper case

private:
    using my = zen::string;
};

} // namespace zen