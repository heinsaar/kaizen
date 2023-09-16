# Examples

Below you can find various examples of code snippets that demonstrate the capabilities of Kaizen.

Simply include the `kaizen.h` header. No additional setup is required.
During development, the `kaizen.h` header is generated during build (see below for building).

### Program arguments
Parse program arguments declaratively:
```cpp
#include "kaizen.h"

int main(int argc, char* argv[])
{
    zen::cmd_args  args(argv, argc);
    bool verbose = args.accept("-verbose").is_present();
    bool ignore  = args.accept("-ignore" ).is_present();
    
    // Or sometime later
    if (args.is_present("-ignore"))
}
```
### Working with files
Open a file and read any line right away:
```cpp
zen::filesystem::filestring filestr("../LICENSE.txt"_path);
zen::string version       = filestr.getline(1);
zen::string license       = filestr.getline(3);
```
### Simple ranges
Python-like range notation:
```cpp
for (int i : zen::in(5))        // i from 0 to 4
for (int i : zen::in(1, 10))    // i from 1 to 9
for (int i : zen::in(0, 10, 2)) // i from 0 to 8, step 2
```
### Strings
Python-like substring extractions:
```cpp
// indices ----> 012345678912345
zen::string z = "Test substrings";

z.substring(  0,   4) == "Test");        // both arguments are indices
z.substring(-20,   4) == "Test");        // negative indices are okay
z.substring(  0,  -5) == "Test subst");  // just like in Python
z.substring(100, 300) == "");            // out-of-bounds indices are okay too
z.substring(  5,  50) == "substrings");  // just like in Python
```
Rich extraction methods from strings, both arbitrary patterns and common cases:
```cpp
z = "Hey, [Hello World] 1.2.3 amazing 1/2/2023";

z.starts_with("Hey"))                    // true
z.extract_between('[', ']');             // "Hello World"
z.extract_version();                     // "1.2.3"
z.extract_pattern(R"((\d+\.\d+\.\d+))"); // "1.2.3"
z.extract_date();                        // "1/2/2023"
z.extract_pattern(R"((\d+\/\d+\/\d+))"); // "1/2/2023"

// A drop-in replacement for std::string
std::string x = z; z = x; // and so on
```
Replace a substring:
```cpp
z = "I love apples, apples, apples";
z.replace(    "apples", "oranges"); // "I love oranges, apples, apples"
z.replace_all("apples", "oranges"); // "I love oranges, oranges, oranges"
```
Remove a substring:
```cpp
z = "Some uninteresting text";
z.remove("uninteresting ");     // "Some text"
```
Trim whitespaces:
```cpp
z =         "   Trim   me  ";
z.trim();   // "Trim   me" - from leading & trailing empty spaces
z.deflate() // "Trim me"   - any adjacent spaces are removed
```
Replicate a pattern of a string:
```cpp
zen::replicate("/", 10) == "//////////";
zen::replicate(10, "*") == "**********";
```
### Random numbers
Just give me a simple random number for everyday use:
```cpp
int n = zen::random_int();    // by default between 0 and 10
int m = zen::random_int(1, 5) // or specify another range
```
### Printing & Logging
Python-like printing with additional logging utilities:
```cpp
std::vector<int> v = {1, 2, 3}
zen::print(v);                  // [1, 2, 3]
zen::print(v, "4", 5);          // [1, 2, 3] 4 5
```
Or even:
```cpp
std::vector<std::vector<int>> v = { {1, 2}, {3, 4} };
zen::print(v);                  // [[1, 2], [3, 4]]
```
In addition, `zen::log()` is equivalent to `zen::print()` except that it will automatically append a new line:
```cpp
zen::log(v, "4", 5); // equivalent to zen::print(v, "4", 5, '\n');
```
### Containers
Richer containers with many useful functions:
```cpp
zen::vector<int> v;
zen::populate_random(v);  // randomly populate anything resizable & iterable
if (v.contains(42)) {     // easily check for containment
    zen::sum(v);          // easily sum up anything iterable with addable elements
}

// A drop-in replacement for std::vector
std::vector x = v; v = x; // and so on
```
The standard `container::empty()` can ambiguously be read as a verb, so Kaizen provides `is_empty()`:
```cpp
if (v.is_empty())     // same as v.empty()
if (zen::is_empty(c)) // same as c.empty(), works with any iterable container c
```
### Quick tests
Sprinkle around some test cases with `ZEN_EXPECT` accepting any expression and reporting it if it fails:
```cpp
const zen::string z = "Test Case";
const zen::vector v = {1, 2, 3, 4};
ZEN_EXPECT(z.ends_with("Case"));     // pass
ZEN_EXPECT(v.contains(7));           // fails, prints: CASE FAIL: ... EXPECTED: v.contains(7)
```
A static assert that shows the expression that failed:
```cpp
// Will show something like:
// 'ZEN STATIC ASSERTION FAILED. "FAILED EXPRESSION:": zen::is_iterable_v<int>'
ZEN_STATIC_ASSERT(zen::is_iterable_v<int>, "FAILED EXPRESSION:");
```
### Versions
Semantic versioning:
```cpp
zen::version v1(1, 2, 3, 4567); // construct from numbers

// Expect
v1.major() ==    1;
v1.minor() ==    2;
v1.patch() ==    3;
v1.build() == 4567;

zen::version  v8("8.2.3.4567"); // construct from a string

// Expect
v8.major() ==    8;
v8.minor() ==    2;
v8.patch() ==    3;
v8.build() == 4567;

// Expect
v1 != v8;
v1 <  v8;
v8 >  v1;

using namespace zen::literals::version;

auto v7 = "7.6.5.4321"_version; // construct using string literals
v7.build()    == 4321;
```
