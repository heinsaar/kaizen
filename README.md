# kaizen

Utility code for most C++ projects.

**At the moment in alpha, with lots of code having very low melting point.**

See [RAPID Practice](https://leoheinsaar.blogspot.com/p/rapid-practice.html) for conventions on issues & commit messages.

Follow the steps described below to run it on your system.

## Windows

In Visual Studio, just open the repo folder and run the ```main()``` function.

In Visual Studio Code, you'll need to do [a few configurations](https://www.youtube.com/watch?v=G9gnSGKYIg4) for your environment first.

## Linux (including [WSL](https://learn.microsoft.com/en-us/windows/wsl/install))

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

   *Advanced*: If you need to specify a particular version of g++ or any other build options, you can do so with additional arguments. For example, to set the C++ compiler to g++, you could use:

   ```bash
   cmake -DCMAKE_CXX_COMPILER=g++ ..
   ```

5. **Compile the Project:** After configuring, you can compile the project with:

   ```bash
   make
   ```

6. **Run the Executable:** If the build is successful, you can run the resulting executable from the build directory:

   ```bash
   ./program_name
   ```

If everything is set up correctly in your `CMakeLists.txt` file and your code is compatible with Linux, these steps should configure and build your project on a Linux system.

Keep in mind that if your project has specific dependencies or requires special configuration, additional steps may be necessary. This might include installing required libraries or tools on your Linux system or adding specific flags and options to the CMake command. But for a typical C++ project, the steps outlined above should be sufficient.
