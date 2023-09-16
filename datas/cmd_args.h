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
#include <stdexcept>
#include <string>
#include <vector>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::vector

// Usage:
// int main(argc, argv)
// ...
// zen::cmd_args        cmd_args(argv, argc);
// const bool verbose = cmd_args.accept("-verbose").is_present();
// const bool ignore  = cmd_args.accept("-ignore" ).is_present();

// TODO: Enhance with support for:
// - Help strings
// - arg arguments (like -path "/to/some/dir"
class cmd_args {
public:
    cmd_args() : argv_(nullptr), argc_(0) {}

    cmd_args(const char* const* argv, int argc)
        : argv_(argv), argc_(argc)
    {
        // Check for consistency between argv and argc for
        // the rare cases when they do not come from main()
        if (argc < 0) {
            throw std::invalid_argument("CONSTRUCTOR ARGUMENT argc MUST BE NON-NEGATIVE");
        }
        for (int i = 0; i < argc; ++i) {
            if (argv[i] == nullptr) {
                throw std::invalid_argument("CONSTRUCTOR ARGUMENT argv CONTAINS nullptr ELEMENT(S)");
            }
        }
    }

    auto& accept(const std::string& a)
    {
        args_accepted_.push_back(a);
        return *this;
    }

    // Returns true if either the provided argument 'a' or the last argument added by accept()
    // is present in the command line (with which the program was presumably launched)
    bool is_present(const std::string& a = "") const
    {
        if (a.empty())
            return args_accepted_.empty() ? false : is_present(args_accepted_.back());

        for (int i = 0; i < argc_; ++i)
            if (a == arg_at(i))
                return true;

        return false;
    }

    std::string arg_at(const int n) const
    {
        if (0 <= n && n < argc_)
            return argv_[n];
        return "";
    }

    std::string first_arg() const { return arg_at(0); }
    std::string  last_arg() const { return arg_at(argc_ - 1); }

private:
    using arguments = std::vector<std::string>;

    const char* const* argv_;
    const int          argc_;
    arguments          args_accepted_;
};

} // namespace zen