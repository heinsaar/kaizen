#pragma once

#include <ostream>
#include <regex>
#include <stdexcept>

namespace zen {

class version : public zen::array<int,4> {
public:
    version(int major, int minor, int patch, int build)
        : zen::array<int,4>{major, minor, patch, build}
    {}

    explicit version(const zen::string& text)
    {
        static const std::regex rx_version{R"((\d+)\.(\d+)\.(\d+)\.(\d+))"};
        if (std::smatch sm; std::regex_match(text, sm, rx_version)) {
            at(0) = std::stoi(sm[1]);
            at(1) = std::stoi(sm[2]);
            at(2) = std::stoi(sm[3]);
            at(3) = std::stoi(sm[4]);
        }
        else {
            throw std::invalid_argument{"The given text does not match the version string pattern."};
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

namespace version_literals {

version operator""_version(const char* text, size_t)
{
    return version{text};
}

} // namespace version_literals

} // namespace zen
