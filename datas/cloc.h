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
#include <vector>
#include <string>

namespace zen {

///////////////////////////////////////////////////////////////////////////////////////////// zen::cloc

// Counts lines of code, use like this:
// 
// zen::cloc cloc(zen::parent_path(), { "datas", "functions", "tests" });
// cloc.count({    ".h",     ".cpp",     ".py" });
// cloc.count({ R"(\.h)", R"(\.cpp)", R"(\.py)" };
// 
// Name is based onthe popular utility cloc: https://github.com/AlDanial/cloc
struct cloc {

    cloc()
        : root_(std::filesystem::current_path()), dirs_({ "." }) {}

    cloc(const std::filesystem::path& root, const std::vector<std::string>& dirs) 
        : root_(root), dirs_(dirs) {}

    int count(const std::vector<std::string>& extensions) const {
        int total_loc = 0;
        for (const auto& dir : dirs_) {
            total_loc += count_in(root_ / dir, extensions);
        }
        return total_loc;
    }

    int count_in(const std::filesystem::path& dir, const std::vector<std::string>& extensions) const {
        int dir_loc = 0;
        for (const auto& file : std::filesystem::recursive_directory_iterator(dir)) {
            if (file.is_regular_file()) {
                const std::string ext = file.path().extension().string();
                if (matches_any(ext, extensions)) {
                    [[maybe_unused]] int loc = dir_loc += count_in_file(file.path());
                    //std::cout << "LOC" << std::setw(5) << loc << " - " << file.path().string() << std::endl; // DEBUG
                }
            }
        }
        return dir_loc;
    }

    int count_in_file(const std::filesystem::path& filename) const {
        std::ifstream file(filename.string());
        std::string line;
        int loc = 0;
        while (std::getline(file, line)) {
            if (std::regex_match(line, std::regex(R"(^\s*[^/\*\\].*\r?$)"))) {
                ++loc;
            }
        }
        return loc;
    }

private:
    bool matches_any(const std::string& ext, const std::vector<std::string>& extensions) const {
        for (const auto& pattern : extensions) {
            if (std::regex_match(ext, std::regex(pattern))) {
                return true;
            }
        }
        return false;
    }

private:
	std::filesystem::path	 root_; // project root
	std::vector<std::string> dirs_; // where to count
};

} // namespace zen