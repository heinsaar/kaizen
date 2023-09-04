# Kaizen

Utility code for C++ projects in a single header file ```kaizen.h```.

**AT THE MOMENT IN ACTIVE DEVELOPMENT, WITH LOTS OF CODE HAVING VERY LOW MELTING POINT.**

## Ways to contribute

1. **Review code & commits.** Our commits follow the [RAPID Practice](https://leoheinsaar.blogspot.com/p/rapid-practice.html) and are very easy to review.
2. **Suggest a utility** If you have an idea for a useful data structure, a member function, or an independent function, feel free to suggest.
3. **Implement an issue or a TODO in code.**
4. **Add more tests.** There can never be enough tests as long as they're independent and cover anything not previously covered.

See [RAPID Practice](https://leoheinsaar.blogspot.com/p/rapid-practice.html) for conventions on issues & commit messages.

## Prerequisites for building

You'll need GCC for Linux or MSVC (comes with Visual Studio) for Windows development.

The project is probably more backward-compatible, but at the moment is being developed and tested with the following tools: 

1. Python 3.11
2. MSVC 19.37
1. GCC 9.4.0

Open the repo folder in your favorite IDE (on Windows, if you're not very used to Visual Studio,
I recommend using Visual Studio Code) and follow the steps described below to run it on your system. The ```main()``` function simply runs the tests.

## Build & Run on Windows & Linux (including [WSL](https://learn.microsoft.com/en-us/windows/wsl/install))

1. **Open a Terminal:** You can open a terminal window by searching for "Terminal" in your Linux desktop's application menu or by using the keyboard shortcut (usually `Ctrl+Alt+T`).

2. **Navigate to Project Directory:** Use the `cd` command to navigate to the directory where your project's `CMakeLists.txt` file is located. Replace `path/to/your/project` with the actual path:

   ```bash
   cd path/to/your/project
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
This will generate convenience utility scripts `runbuild_win.bat` and `runbuild_linx.sh` that combine the next steps 5 and 6, so you can only call the corresponding script for your environment.

   *Advanced*: If you need to specify a particular version of g++ or any other build options, you can do so with additional arguments. For example, to set the C++ compiler to g++, you could use:

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

The tests will run and show their outputs in the console that will begin like this:
```
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
|||||||||||||||||||||||||||| KAIZEN 1.0.0 ||||||||||||||||||||||||||||
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
RUNNING TESTS...
```
