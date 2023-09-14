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

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace zen {

// Forward declarations
template <class T, class... Args> void log(T x, Args... args);

namespace file {

///////////////////////////////////////////////////////////////////////////////////////////// zen::filestring

class filestring {
public:
    filestring(const std::filesystem::path& path)
        : filepath_(path), filestream_(path)
    {
        if (!filestream_.is_open()) {
            zen::log("ERROR OPENING FILE: ", path);
            throw std::runtime_error("END OF FILE REACHED");
        }
    }

    ~filestring() {
        if (filestream_.is_open()) {
            filestream_.close();
        }
    }

    class iterator {
    public:
        iterator(std::ifstream& is, bool end_marker = false)
            : input_{is}, end_marker_{end_marker}
        {
            if (!end_marker_) {
                input_.clear();
                input_.seekg(0, std::ios::beg);
                this->operator++();
            }
        }

        bool operator!=(const iterator& it) const {
            return it.end_marker_ != end_marker_;
        }
        
        const std::string& operator*() const {
            return line_;
        }

        iterator& operator++() {
            if (input_.eof())
                end_marker_ = true;
            else
                std::getline(input_, line_, '\n');

            return *this;
        }

    private:
        std::ifstream& input_;
        bool           end_marker_{false};
        std::string    line_;
    };

    auto begin() { return iterator{filestream_}; }
    auto end()   { return iterator{filestream_, true}; }

    // Method to get line n from the file (indexing starts from 1, not 0)
    std::string getline(int nth) {
        auto it = begin();
        while (--nth > 0 && it != end()) {
            ++it;
        }

        if (nth != 0)
            throw std::out_of_range("END OF FILE REACHED");

        return *it;
    }

private:
    // TODO: Dynamically cache lines that are read the first time
    const std::filesystem::path& filepath_;
    std::ifstream                filestream_;
};

namespace literals {
namespace path {

std::filesystem::path operator "" _path(const char* str, std::size_t length)
{
    return std::filesystem::path(std::string(str, length));
}

}}

} // namespace file
} // namespace zen