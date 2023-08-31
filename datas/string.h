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

#include <string>

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
    
#if __cplusplus < 202303L // check pre-C++23, at which point std::string::contains() is standard
    // SFINAE to ensure that this version is only enabled when Pred is callable
    template<class Pred, typename = std::enable_if_t<std::is_invocable_r_v<bool, Pred, char>>>
    bool contains(const Pred& p)            const { return std::find_if(my::begin(), my::end(), p) != my::end(); }
    bool contains(const std::string_view s) const { return find(s) != std::string::npos; }
#endif

    // For some string s = "[EXTRACTME]"; 
    // ......................^^^^^^^^^...
    // Usage: s.extract_between("[", "]");
    std::string extract_between(const std::string_view beg, const std::string_view end) const
    {
        const size_t posBeg = find(beg);
        if (posBeg == std::string::npos)
            return ""; // signals 'not found'
        const size_t posEnd = find(end, posBeg + 1);
        if (posEnd == std::string::npos)
            return ""; // signals 'not found'
        return substr(posBeg + 1, posEnd - posBeg - 1);
    }

    // Modifying functions
    string& prefix(const std::string_view s)
    {
        insert(0, s);
        return *this;
    }

    string& replace_all(const std::string_view oldStr, const std::string_view newStr)
    {
        size_t startPos = 0;
        while ((startPos = find(oldStr, startPos)) != std::string::npos) {
            replace(startPos, oldStr.length(), newStr);
            startPos += newStr.length(); // handles the case of 'newStr' being a substring of 'oldStr'
        }
        return *this;
    }

    string& trim_from_last(const std::string_view str)
    {
        *this = substr(0, rfind(str));
        return *this;
    }

    // TODO: Implement these
    // From Deel:
    // deflate()
    // 
    // From Python string
    // capitalize()	    Converts the first character to upper case
    // tolower()	    Converts string into lower case
    // center()	        Returns a centered string
    // endswith()	    Returns true if the string ends with the specified value
    // isalnum()	    Returns True if all characters in the string are alphanumeric
    // isalpha()	    Returns True if all characters in the string are in the alphabet
    // isascii()	    Returns True if all characters in the string are ascii characters
    // isdecimal()	    Returns True if all characters in the string are decimals
    // isdigit()	    Returns True if all characters in the string are digits
    // isidentifier()	Returns True if the string is an identifier
    // islower()	    Returns True if all characters in the string are lower case
    // isnumeric()	    Returns True if all characters in the string are numeric
    // isprintable()	Returns True if all characters in the string are printable
    // isspace()	    Returns True if all characters in the string are whitespaces
    // isupper()	    Returns True if all characters in the string are upper case
    // ljust()	        Returns a left justified version of the string
    // lstrip()	        Returns a left trim version of the string
    // maketrans()	    Returns a translation table to be used in translations
    // partition()	    Returns a tuple where the string is parted into three parts
    // rfind()	        Searches the string for a specified value and returns the last position of where it was found
    // rjust()	        Returns a right justified version of the string
    // rpartition()	    Returns a tuple where the string is parted into three parts
    // rsplit()	        Splits the string at the specified separator, and returns a list
    // rstrip()	        Returns a right trim version of the string
    // split()	        Splits the string at the specified separator, and returns a list
    // splitlines()	    Splits the string at line breaks and returns a list
    // strip()	        Returns a trimmed version of the string
    // swapcase()	    Swaps cases, lower case becomes upper case and vice versa
    // toupper()	    Converts a string into upper case

private:
    using my = string;
};

} // namespace zen