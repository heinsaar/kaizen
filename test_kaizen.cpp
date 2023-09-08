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

#include "test_kaizen.h"

int main(int argc, char* argv[])
{
	// Extract Kaizen version from the license file
	zen::filestring		  textfile("../LICENSE.txt");
	zen::string	line    = textfile.getline(1);
	const zen::string v = line.extract_pattern(R"((\d+\.\d+\.\d+))"); // version
	
	// Print the Kaizen preamble
	zen::print(zen::color::blue("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"));
	zen::print(zen::color::blue("|||||||||||||||||||||||||||| KAIZEN"), v, zen::color::blue("||||||||||||||||||||||||||||\n"));
	zen::print(zen::color::blue("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"));
	zen::print(zen::color::blue("RUNNING TESTS...\n"));

///////////////////////////////////////////////////////////////////////////////////////////// SANITY TESTS
	sanitest_cmd_args(argc, argv);

	// Test data structures
	sanitest_filestring();
    sanitest_version();
	sanitest_string();
	sanitest_vector();
	sanitest_array();
	sanitest_deque();
	sanitest_list();

	// Test utilities
	sanitest_utils();

///////////////////////////////////////////////////////////////////////////////////////////// MAIN TESTS
	test_string_substring();
	test_string_ends_with();
	test_string_extract();
	
	//ZEN_EXPECT(!"DEMO FAIL"); // comment & uncomment this to see a fail

	const bool        all_tests_pass = !zen::TEST_CASE_FAIL_COUNT.load();
	const auto FAIL = all_tests_pass ?  zen::color::nocolor("FAIL:") : zen::color::red("FAIL:");

	zen::log("TOTAL TEST CASES", zen::color::green("PASS:"), zen::TEST_CASE_PASS_COUNT.load());
	zen::log("TOTAL TEST CASES",                    FAIL,    zen::TEST_CASE_FAIL_COUNT.load());
	
	if (all_tests_pass) {
		zen::log(zen::color::green("--------------------"));
		zen::log(zen::color::green("  ALL TESTS PASS "   ));
		zen::log(zen::color::green("--------------------"));
	}
}
