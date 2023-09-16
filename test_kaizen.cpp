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
	const auto project_dir = zen::search_upward(std::filesystem::current_path(), "kaizen").value();

	zen::cmd_args		  cmd_args(argv, argc);
	zen::REPORT_TC_PASS = cmd_args.accept("-report_tc_pass").is_present();

///////////////////////////////////////////////////////////////////////////////////////////// PREAMBLE

	// Extract Kaizen version from the license file
	zen::file::filestring textfile(project_dir / "LICENSE.txt");
	zen::string	   line = textfile.getline(1);
	zen::string	   vers = line.extract_version();
	
	std::string time      = R"((\d+\:\d+\:\d+))";
	std::string datestamp = zen::string(zen::timestamp()).remove(time).deflate();

	// Print the Kaizen preamble
	zen::log(zen::color::blue(zen::repeat("|", 79)));
	zen::log(zen::color::blue(zen::repeat("|", 30) + " KAIZEN"), vers,
		     zen::color::blue(zen::repeat("|", 30)));
	zen::log(zen::color::blue(zen::repeat("|", 30) + "  " + datestamp + " "),
		     zen::color::blue(zen::repeat("|", 30)));
	zen::log(zen::color::blue(zen::repeat("|", 79)));
	zen::log(zen::color::blue("RUNNING TESTS..."));

///////////////////////////////////////////////////////////////////////////////////////////// MAIN TESTS

	zen::timer timer;

	main_test_cmd_args(argc, argv);
	main_test_forward_list();
	main_test_filestring();
    main_test_version();
	main_test_string();
	main_test_vector();
	main_test_array();
	main_test_deque();
	main_test_utils();
	main_test_timer();
	main_test_list();
	main_test_in();

	if (cmd_args.is_present("-cloc")) main_test_cloc();

	timer.stop();

	END_TESTS;

///////////////////////////////////////////////////////////////////////////////////////////// REPORT

	//ZEN_EXPECT(!"DEMO FAIL 1"); // comment & uncomment this to see a fail
	//ZEN_EXPECT(!"DEMO FAIL 2"); // comment & uncomment this to see a fail

// ------------------------------------------------------------------------------------------ LOC & LOC/TC ratio

	const zen::cloc cloc(zen::parent_path(), { "build"});
	int total_loc = cloc.count({ ".h" });

	auto ratio = static_cast<double>(total_loc) / (zen::TEST_CASE_PASS_COUNT + zen::TEST_CASE_FAIL_COUNT);

	zen::log(""); // new line
	zen::log(zen::string("TOTAL DURATION (MILLIS):").pad_end(24), timer.duration<zen::timer::msec>());
	zen::log(zen::string("TOTAL kaizen.h LOC:"     ).pad_end(24), total_loc);
	zen::log(zen::string("TOTAL kaizen.h LOC/TC:").pad_end(24), ratio);

// ------------------------------------------------------------------------------------------ Total PASS/FAIL

	const bool             all_tests_pass = !zen::TEST_CASE_FAIL_COUNT.load();
	const auto FAIL      = all_tests_pass ?  zen::color::nocolor("FAIL:") : zen::color::red("FAIL:");
	const auto FAILCOUNT = all_tests_pass
		? zen::color::nocolor(std::to_string(zen::TEST_CASE_FAIL_COUNT.load()))
		: zen::color::red(	  std::to_string(zen::TEST_CASE_FAIL_COUNT.load()));

	zen::log(""); // new line
	zen::log("TOTAL TEST CASES", zen::color::green("PASS:"), zen::color::green(std::to_string(zen::TEST_CASE_PASS_COUNT.load())));
	zen::log("TOTAL TEST CASES", FAIL, FAILCOUNT);
	
	if (all_tests_pass) {
		zen::log(zen::color::green("--------------------"));
		zen::log(zen::color::green("  ALL TESTS PASS "   ));
		zen::log(zen::color::green("--------------------"));
	}
}
