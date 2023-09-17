![Build](https://github.com/heinsaar/kaizen/actions/workflows/cmake-multi-platform.yml/badge.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Kaizen

Collection of utilities and enhanced data structures for a wide range of C++ projects in a single header file ```kaizen.h```

=====================================================================

**AT THE MOMENT IN ACTIVE DEVELOPMENT, WITH LOTS OF CODE HAVING VERY LOW MELTING POINT.**

=====================================================================

## Design Philosophy

Kaizen does not aim to be radiation-hardened for all imaginable scenarios and use cases. Instead, inspired by
the Japanese concept of [Kaizen](https://en.wikipedia.org/wiki/Kaizen), emphasizing frequent and gradual
improvement, this library is built on top of STL and aims to provide a malleable and growing set of practical
and simple tools through a single header file that, like a Swiss army knife, includes just enough of everything
that can be useful for a broad range of C++ projects right off the bat.

So, for example, even though STL containers were not meant to be derived from (in particular, their destructors
are not virtual), `zen::string` derives from `std::string` in order to quickly, without having to implement all
the conversion operators and delegate functions that a composition-based approach would require, provide the ability
to convert to and from `std::string` at any point in the codebase whenever there's need for the richer interface
of working with strings that `zen::string` provides.

This approach is rooted in the philosophy that in the vast majority of cases and projects, the benefits from these
utilities far outweigh any theoretical dangers of for some reason allocating `zen::string` itself dynamically and
then deleting it through a pointer to base `std::string`, whether accidentally or on purpose. Any codebase is far more
likely to experience problems and corrosion from the regular breed of bugs that are much easier to make accidentally.

The `kaizen.h` header is generated during the build (see below for building).

## Examples
Here's a taste of what you can do with Kaizen right out of the box:

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
Open a file and read any line right away:
```cpp
zen::filesystem::filestring filestr("../LICENSE.txt"_path);
zen::string version       = filestr.getline(1);
zen::string license       = filestr.getline(3);
```
Python-like range notation:
```cpp
for (int i : zen::in(5))        // i from 0 to 4
for (int i : zen::in(1, 10))    // i from 1 to 9
for (int i : zen::in(0, 10, 2)) // i from 0 to 8, step 2
```
Python-like substring extractions:
```cpp
// indices ----> 012345678912345
zen::string z = "Test substrings";

z.substring(  0,   4) == "Test");        // both arguments are indices
z.substring(-20,   4) == "Test");        // negative indices are okay
z.substring(  0,  -5) == "Test subst");  // just like in Python
z.substring(100, 300) == "");            // out-of-bounds indices are okay too
z.substring(  5,  50) == "substrings");  // just like in Python

// A drop-in replacement for std::string
std::string x = z; z = x; // and so on
```
Replace a substring:
```cpp
z = "I love apples, apples, apples";
z.replace(    "apples", "oranges"); // "I love oranges, apples, apples"
z.replace_all("apples", "oranges"); // "I love oranges, oranges, oranges"
```
Python-like printing:
```cpp
std::vector<int> v = {1, 2, 3}
zen::print(v);                  // [1, 2, 3]
zen::print(v, "4", 5);          // [1, 2, 3] 4 5
```
Richer containers with many useful functions:
```cpp
zen::vector<int> v;             // declare & use just like std::vector
zen::populate_random(v);        // randomly populate anything resizable & iterable
if (v.contains(42)) {           // easily check for containment
    zen::sum(v);                // easily sum up anything iterable with addable elements
}

// A drop-in replacement for std::vector
std::vector x = v; v = x; // and so on
```
Many more examples can be found [here](https://github.com/heinsaar/kaizen/blob/master/Examples.md).

## Ways to contribute

Circles signify a potential scale of involvement in terms of time and/or energy. Green circles signify the easy stuff, essentially requiring no coding.
Yellow circles signify a potential need to code, although quite often a suggestion would do here as well. Red circles signify a clear need to code.

1. 🟢 **Review code & commits.** Our commits follow the [RAPID Practice](https://leoheinsaar.blogspot.com/p/rapid-practice.html) and therefore are very easy to review.
1. 🟢 **Suggest a utility.** If you have an idea for a common C++ utility code, feel free to suggest in [our discussions](https://github.com/heinsaar/kaizen/discussions).
1. 🟢 **Document.** If you see any missing documentation or a discrepancy (wrong code, etc.).
1. 🟡 **Generalize a utility.** If you see how to generalize any code in a meaningful way, [like this](https://github.com/heinsaar/kaizen/commit/105fa25eeb5a796941e89304d61070afdea88891).
1. 🟡 **Optimize.** If you see how to optimize any code in a meaningful way.
1. 🟡 **Harden.** If you see how to improve the robustness of any code (unhandled edge cases, etc.).
1. 🟡 **Reduce LOC.** If you see ways to reduce lines of code (common sense - with no loss of readability).
1. 🔴 **Implement a utility**. If you have a commonly useful utility piece of code.
1. 🔴 **Resolve an [issue](https://github.com/heinsaar/kaizen/issues)**. Some are in the form of a "TODO" in code.
1. 🔴 **Add tests.** There can never be enough tests that cover anything previously not covered.
1. 🔴 **Automate.** If you see ways to automate any process and thus save iteration time.

See [RAPID Practice](https://leoheinsaar.blogspot.com/p/rapid-practice.html) for conventions on issues & commit messages.

## Prerequisites for building

You'll need the GCC compiler for Linux or MSVC (comes with Visual Studio) for Windows development.

The project is probably more widely and more backward-compatible, but at the moment is being developed and tested with the following tools: 

1. Python 3.11
2. MSVC 19.37
1. GCC 9.4.0

Open the repo folder in your favorite IDE (on Windows, if you're not very used to Visual Studio,
I recommend using Visual Studio Code with [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)) and follow the steps described below to run it on your system.
The `main()` function simply runs the tests and print out the report.

## Build & Run on Windows & Linux (including [WSL](https://learn.microsoft.com/en-us/windows/wsl/install))

1. **Open a Terminal:** You can open a terminal window by searching for "Terminal" in your Linux desktop's application menu or by using the keyboard shortcut (usually `Ctrl+Alt+T`).

2. **Navigate to Project Directory:** Use the `cd` command to navigate to the directory where your project's `CMakeLists.txt` file is located. Replace `path/to/your/cloned/kaizen` with the actual path:

   ```bash
   cd path/to/your/cloned/kaizen
   ```

3. **Create a Build Directory:** It's a good practice to create a separate directory for the build files to keep them isolated from the source files. Inside your project directory, run:

   ```bash
   mkdir build
   cd build
   ```

4. **Configure the Project with CMake:** Now, from inside the `build` directory, run CMake to configure the project. This will read the `CMakeLists.txt` file and generate the necessary Makefiles for building the project. The `..` at the end of the command tells CMake to look in the parent directory for the `CMakeLists.txt` file:

   ```bash
   cmake ..
   ```
This will generate convenience utility scripts `runbuild_win.bat` and `runbuild_linx.sh` that combine the next steps 5 and 6, so you can simply call the corresponding script for your environment.

**NOTE:** This will only work smoothly either within a Linux environment (including [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)) or from within a Windows terminal that's integrated
into Visual Studio (not Visual Studio Code), where the integrated terminal automatically sets up all the necessary environment variables (pointing to the MSVC compiler `cl.exe`, etc.) that are
automatically configured when you run Visual Studio's own developer command prompt.

If you run this from a Windows terminal inside another IDE like Visual Studio Code, you will probably get an error that looks like this:

```bash
-- Building for: NMake Makefiles
-- The C compiler identification is unknown
-- The CXX compiler identification is unknown
CMake Error at CMakeLists.txt:11 (project):
  The CMAKE_C_COMPILER:

    cl

  is not a full path and was not found in the PATH.
```
If you want to develop using MSVC compiler from Visual Studio Code, there are various ways of setting that up, please see online.

   If you need to specify a particular version of g++ or any other build options, you can do so with additional arguments. For example, to set the C++ compiler to g++, you could use:

   ```bash
   cmake -DCMAKE_CXX_COMPILER=g++ ..
   ```

5. **Compile the Project:** After configuring, you can compile the project with:

   ```bash
   cmake --build .
   ```
   
   On Linux, you can also call ```make``` directly (does the same thing).

6. **Run the Executable:** If the build is successful, you can run the resulting executable from the build directory.
  
   Linux:

   ```bash
   ./kaizen
   ```
   Windows:
   ```bash
   .\kaizen.exe
   ```

A build and run will produce a console output that will look like this:

![image](https://github.com/heinsaar/kaizen/assets/14178490/f3a6e3e4-e967-4061-9ce3-0044d7293d92)












