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

#include "alpha.h" // internal; will not be included in kaizen.h

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::string

class string : public std::string, private zen::stackonly
{
public:
    using std::string::string;    // inherit constructors,         has to be explicit
    using std::string::operator=; // inherit assignment operators, has to be explicit

    string(const std::string&     s) : std::string(s) {}
    string(const std::string_view s) : std::string(s) {}

#if __cplusplus < 202303L // check pre-C++23, at which point std::string::contains() is standard
    // SFINAE to ensure that this version is only enabled when Pred is callable
    template<class Pred, typename = std::enable_if_t<std::is_invocable_r_v<bool, Pred, char>>>
    bool contains(const Pred& p)            const { return std::find_if(my::begin(), my::end(), p) != my::end(); }
    bool contains(const std::string_view s) const { return find(s) != std::string::npos; }
#endif

    bool is_empty() const { return my::empty(); }

    // std::string s = "[EXTRACTME]"; 
    //                   ^^^^^^^^^
    // Example: s.extract_between("[", "]");
    zen::string extract_between(const std::string_view beg, const std::string_view end) const
    {
        const size_t posBeg = find(beg);
        if (posBeg == std::string::npos) return ""; // signals 'not found'
        const size_t posEnd = find(end, posBeg + 1);
        if (posEnd == std::string::npos) return ""; // signals 'not found'
        return substr(posBeg + 1, posEnd - posBeg - 1);
    }

    zen::string extract_pattern(const std::string& pattern)
    {
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

    zen::string& remove(const std::string& pattern)
    {
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

    // Behaves like JavaScript's string.replace()
    auto& replace(const std::string& search, const std::string& replacement) {
        const size_t position = std::string::find(search);
        if (position != std::string::npos) {
            std::string::replace(position, search.length(), replacement);
        }
        return *this;
    }

    template <typename Pred>
    auto& replace_if(const std::string& search, const std::string& replacement, Pred predicate)
    {
        if (search.empty()) return *this;

        static_assert(std::is_invocable<Pred, const std::string&>(),
            "TEMPLATE PARAMETER Pred MUST BE CALLABLE WITH const std::string&, BUT IS NOT");
        static_assert(std::is_same_v<std::invoke_result_t<Pred, const std::string&>, bool>,
            "TEMPLATE PARAMETER Pred MUST RETURN bool, BUT DOES NOT");

        const size_t position = std::string::find(search);
        if (position != std::string::npos && predicate(*this)) {
            std::string::replace(position, search.length(), replacement);
        }
        return *this;
    }

    // Behaves like JavaScript's string.replaceAll()
    auto& replace_all(const std::string& search, const std::string& replacement)
    {
        if (search.empty()) return *this;

        size_t pos = 0;
        while ((pos = my::find(search, pos)) != std::string::npos) {
            std::string::replace(pos, search.length(), replacement);
            pos += replacement.length(); // move pos forward by the length of replace to prevent infinite loops
        }
        return *this;
    }

    template <typename Pred>
    auto& replace_all_if(const std::string& search, const std::string& replacement, Pred predicate)
    {
        if (search.empty()) return *this;

        static_assert(std::is_invocable<Pred, const std::string&>(),
            "TEMPLATE PARAMETER Pred MUST BE CALLABLE WITH const std::string&, BUT IS NOT");
        static_assert(std::is_same_v<std::invoke_result_t<Pred, const std::string&>, bool>,
            "TEMPLATE PARAMETER Pred MUST RETURN bool, BUT DOES NOT");

        size_t pos = 0;
        while ((pos = my::find(search, pos)) != std::string::npos) {
            if (predicate(*this)) {
                std::string::replace(pos, search.length(), replacement);
                pos += replacement.length(); // move pos forward by the length of replace to prevent infinite loops
            } else {
                pos += search.length(); // move pos forward by the length of search
            }
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

    bool is_trimmed()
    {
        return !::isspace(my::front()) &&!::isspace(my::back());
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

    auto substring(int i1, int i2) const
    {
        const int sz = static_cast<int>(size());

        // If necessary, convert negative indices to positive
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

    auto& pad_start(size_t target_length, const std::string& pad_string = " ")
    {
        if (pad_string.empty()) return *this;

        const size_t current_length = my::size();
        const size_t total_padding_needed = target_length > current_length ? target_length - current_length : 0;

        // Full pad strings
        const size_t full_pads = total_padding_needed / pad_string.length();

        // Remaining characters
        const size_t remaining = total_padding_needed % pad_string.length();

        // Generate the padding string
        std::string padding;
        for (size_t i = 0; i < full_pads; ++i) {
            padding += pad_string;
        }
        padding += pad_string.substr(0, remaining);

        my::insert(0, padding);

        return *this;
    }

    auto& pad_end(size_t target_length, const std::string& pad_string = " ")
    {
        if (pad_string.empty()) return *this;

        while (my::size() < target_length) {
            // Append as much of pad_string as will fit
            my::append(pad_string, 0, std::min(pad_string.size(), target_length - my::size()));
        }

        return *this;
    }

    auto& capitalize()
    {
        if (is_empty()) return *this;

        if (std::isalpha(front()) && std::islower(front())) {
            my::front() = static_cast<char>(std::toupper(my::front())); // capitalize the first character
        }

        for (size_t i = 1; i < my::size(); ++i) {
            char& c = my::at(i);
            if (std::isalpha(c) && std::isupper(c)) {
                c = static_cast<char>(std::tolower(c));
            }
        }

        return *this;
    }

    auto& to_lower() {
        for (auto& c : *this) {
            if (std::isalpha(c) && std::isupper(c)) {
                c = static_cast<char>(std::tolower(c));
            }
        }
        return *this;
    }

    auto& to_upper() {
        for (auto& c : *this) {
            if (std::isalpha(c) && std::islower(c)) {
                c = static_cast<char>(std::toupper(c));
            }
        }
        return *this;
    }

    auto& center(size_t width, char fillchar = ' ') {
        if (width <= my::size()) return *this;

        const size_t padding = width - my::size();
        const size_t left_padding  = padding / 2;
        const size_t right_padding = padding - left_padding;

        my::insert(0, left_padding, fillchar);
        my::append(right_padding, fillchar);

        return *this;
    }

    bool is_printable() const { return                std::all_of(my::begin(), my::end(), [](auto c) { return std::isprint(c); }); }
    bool is_alnum()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::isalnum(c); }); }
    bool is_alpha()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::isalpha(c); }); }
    bool is_digit()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::isdigit(c); }); }
    bool is_lower()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::islower(c); }); }
    bool is_upper()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::isupper(c); }); }
    bool is_space()     const { return !is_empty() && std::all_of(my::begin(), my::end(), [](auto c) { return std::isspace(c); }); }

    bool is_identifier() const
    {
        if (is_empty())
            return false;

        if (!std::isalpha(front()) && front() != '_')
            return false;

        for (size_t i = 1; i < my::size(); ++i) {
            const char& c = my::at(i);
            if (!std::isalnum(c) && c != '_') {
                return false;
            }
        }

        return true;
    }

    auto& ljust(int width, char fillchar = ' ')
    {
        if (width < 0)
            width = 0; // handle negative width gracefully

        auto uwidth = static_cast<std::string::size_type>(width);
        if (uwidth <= my::size())
            return *this;

        const size_t padding = uwidth - my::size();
        my::append(padding, fillchar);

        return *this;
    }

    auto& rjust(int width, char fillchar = ' ')
    {
        if (width < 0)
            width = 0; // handle negative width gracefully

        auto uwidth = static_cast<std::string::size_type>(width);
        if (uwidth <= my::size())
            return *this;

        const std::string::size_type padding = uwidth - my::size();
        my::insert(0, padding, fillchar);

        return *this;
    }

    auto& rtrim()
    {
        my::erase(
            std::find_if(my::rbegin(), my::rend(),
                [](int c) { return !std::isspace(c); }
            ).base(),
            my::end()
        );
        return *this;
    }

    auto& ltrim()
    {
        my::erase(
            my::begin(),
            std::find_if(my::begin(), my::end(), [](int c) { return !std::isspace(c); })
        );
        return *this;
    }

    auto partition(const std::string& separator) 
    {
        if (separator.empty())
            throw std::invalid_argument("STRING SEPARATOR CANNOT BE EMPTY");

        const std::string_view sv(my::data(), my::size());
        const size_t pos = my::find(separator);

        if (pos == std::string::npos)
            return std::make_tuple(sv, std::string_view(), std::string_view());

        const std::string_view before = sv.substr(0, pos);
        const std::string_view after  = sv.substr(pos + separator.length());
        const std::string_view sep    = sv.substr(pos,  separator.length());

        return std::make_tuple(before, sep, after);
    }

    auto rpartition(const std::string& separator)
    {
        if (separator.empty())
            throw std::invalid_argument("STRING SEPARATOR CANNOT BE EMPTY");

        const std::string_view sv(my::data(), my::size());
        const size_t pos = my::rfind(separator);

        if (pos == std::string::npos)
            return std::make_tuple(sv, std::string_view(), std::string_view());

        const std::string_view before = sv.substr(0, pos);
        const std::string_view after  = sv.substr(pos + separator.length());
        const std::string_view sep    = sv.substr(pos,  separator.length());

        return std::make_tuple(before, sep, after);
    }

    std::vector<zen::string> split(const std::string& separator)
    {
        // TODO: can be template to support any container
        std::vector<zen::string> result;
        std::string s(*this);
        std::string token;
        size_t pos = 0;
        while ((pos = s.find(separator)) != std::string::npos) {
            token = s.substr(0, pos);
            result.push_back(token);
            s.erase(0, pos + separator.length());
        }
        result.push_back(s);
        return result;
    }

    std::vector<zen::string> split_lines()
    {
        std::vector<zen::string> lines;
        std::istringstream f(*this);
        std::string line;
        while (std::getline(f, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    auto& swapcase()
    {
        for (auto& c : *this) {
            if (std::isalpha(c)) {
                c = std::islower(c) ? static_cast<char>(std::toupper(c)) : static_cast<char>(std::tolower(c));
            }
        }
        return *this;
    }

private:
    using my = zen::string;
};

struct string_hash {
    size_t operator()(const zen::string& z) const {
        return std::hash<std::string>()(z);
    }
};

} // namespace zen

