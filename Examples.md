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
    zen::cmd_args   cmd_args(argv, argc);
    bool small    = cmd_args.accept("-verbose").is_present();
    bool ignore   = cmd_args.accept("-ignore" ).is_present();
        
    // Or sometime later
    if (cmd_args.is_present("-ignore"))
}
```
### Working with files
Open a file and read any line right away:
```cpp
zen::filestring       filestr("../LICENSE.txt");
zen::string version = filestr.getline(1);
zen::string license = filestr.getline(3);
```
### Simple ranges
Python-like range notation:
```cpp
for (int i : zen::in(5))        // i from 0 to 4
for (int i : zen::in(1, 10))    // i from 1 to 9
for (int i : zen::in(0, 10, 2)) // i from 0 to 8, step 2
```
### Strings
Python-like string manupulations:
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

// Fully interchangeable with std::string
std::string x = z; z = x; // and so on
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
### Containers
Richer containers with many useful functions:
```cpp
zen::vector<int> v;
zen::populate_random(v);
if (v.contains(42)) {
    zen::print(v);              // will print the contents, like [4, 2, 5, 7, 6]
    zen::print("Contents:", v); // any number of arguments, like in Python
}

// Fully interchangeable with std::vector
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

ZEN_EXPECT(v1.major() ==    1);
ZEN_EXPECT(v1.minor() ==    2);
ZEN_EXPECT(v1.patch() ==    3);
ZEN_EXPECT(v1.build() == 4567);

zen::version  v8("8.2.3.4567"); // construct from a string
ZEN_EXPECT(v8.major() ==    8);
ZEN_EXPECT(v8.minor() ==    2);
ZEN_EXPECT(v8.patch() ==    3);
ZEN_EXPECT(v8.build() == 4567);

// Compare versions
ZEN_EXPECT(v1 != v8);
ZEN_EXPECT(v1 <  v8);
ZEN_EXPECT(v8 >  v1);

using namespace zen::version_literals;
auto v7 = "7.6.5.4321"_version; // construct using string literals
ZEN_EXPECT(v7.build() == 4321);
```
