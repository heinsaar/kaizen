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

#include <stdexcept>
#include <ostream>
#include <regex>

namespace zen {

// One Linux system gave the warning: In the GNU C Library, "major" is defined
// by <sys/sysmacros.h>. For historical compatibility, it is currently defined
// by <sys / types.h> as well, but we plan to remove this soon. To use "major",
// include < sys / sysmacros directly. If you did not intend to use a system-defined
// macro "major", you should undefine it after including <sys/types.h>.
// So we undefine them:
#undef major
#undef minor

///////////////////////////////////////////////////////////////////////////////////////////// zen::version
// Example: zen::version v8("8.2.3.4567");
// Example: zen::version v1(1, 2, 3, 4567);
// v1.major() == 1;
// v1.minor() == 2;
// v1.patch() == 3;
// v1.build() == 4567;
class version : public std::array<int, 4> { 
public:
    version(int major, int minor, int patch, int build)
        : std::array<int, 4>{major, minor, patch, build}
    {}

    explicit version(const std::string& text)
    {
        static const std::regex rx_version{R"((\d+)\.(\d+)\.(\d+)\.(\d+))"};
        if (std::smatch sm; std::regex_match(text, sm, rx_version)) {
            at(0) = std::stoi(sm[1]);
            at(1) = std::stoi(sm[2]);
            at(2) = std::stoi(sm[3]);
            at(3) = std::stoi(sm[4]);
        } else {
            throw std::invalid_argument{
                // Any cost of typeid is likely to be dwarfed by the cost of the exception anyway
                std::string(typeid(*this).name()) + " CONSTRUCTOR ARGUMENT STRING DOESN'T MATCH THE EXPECTED M.M.P.B PATTERN."
            };
        }
    }

    constexpr auto major() const { return at(0); }
    constexpr auto minor() const { return at(1); }
    constexpr auto patch() const { return at(2); }
    constexpr auto build() const { return at(3); }
};

std::ostream& operator<<(std::ostream& os, const version& v)
{
    return os << v.major() << '.' << v.minor() << '.' << v.patch() << '.' << v.build();
}

namespace literals::version {

// Example: auto v7 = "7.6.5.4321"_version;
zen::version operator""_version(const char* text, size_t)
{
    return zen::version{text};
}

} // namespace literals::version

} // namespace zen
