The `kaizen.h` header is generated during build (see below for building).

Here's a taste of what you can do with Kaizen right out of the box:

## Random numbers
```cpp
#include "kaizen.h"

// Just give me a simple random number for everyday use
int n = zen::random_int(); // by default between 0 and 10
```
## Containers
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
## Strings
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
And more:
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
## Quick test cases
Sprinkle around some test cases with `ZEN_EXPECT` accepting any expression and reporting it if it fails:
```cpp
const zen::string z = "Test Case";
const zen::vector v = {1, 2, 3, 4};
ZEN_EXPECT(z.ends_with("Case"));     // pass
ZEN_EXPECT(v.contains(7));           // fails, prints: CASE FAIL: ... EXPECTED: v.contains(7)
```

## Working with files
Open a file and read any line right away:
```cpp
zen::filestring       filestr("../LICENSE.txt");
zen::string version = filestr.getline(1);
zen::string license = filestr.getline(3);
```