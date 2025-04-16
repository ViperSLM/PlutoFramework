<p align="center">
  <img src="https://viperslm.com/resources/pluto-framework/logo-shadow.png" alt="Pluto Framework" />
</p>

# About
The main purpose behind the Pluto Framework library is to establish a simple loop when writing applications. On top of this, a module system is implemented to aid with the creation of subsystems to extend the library's functionality.

# Building
## Pre-requisites:
* C++ compiler w/ support for C++17 (tested with MSVC, GCC and Clang)
  - ***Windows:** You can use either Visual Studio or MinGW-W64 (custom toolchain or through MSYS2)*
  - ***Unix/Unix-like OS's (Linux, FreeBSD/OpenBSD, Solaris/illumos, etc.):** GCC or Clang can be installed by either compiling manually or through a package manager*
  - ***macOS:** Clang can be installed by installing the Xcode Command Line Tools via the Terminal: `sudo xcode-select --install`*
* CMake 3.20 or higher

## Instructions:

For most platforms, the framework library can be built by doing the following:
1. Create a new folder in the repository *(e.g. build)* which will serve as the main build directory
2. Under a command-line *(e.g. Command Prompt under Windows or Bash under Linux), invoke CMake to set up the build directory by typing in the following (assuming you named the folder 'build'):*
   
   `cmake -B build`
   
   **NOTE:** If you want to build the framework as a shared library, append '-DBUILD_SHARED_LIBS=ON' while invoking cmake:

   `cmake -B build -DBUILD_SHARED_LIBS=ON`

   Additionally, if you also want to build the example programs, also append '-DPLUTO_BUILD_EXAMPLES=ON':

   `cmake -B build -DPLUTO_BUILD_EXAMPLES=ON`

4. After the above command is finished, you can build the library by typing the following:
   
   `cmake --build build`
6. If the build was successful, you should see the resulting library and example executable(s) inside the build folder.

The core of the framework library itself doesn't need any dependencies apart from a C/C++ compiler w/ C++17 support and CMake.
However, some modules might have some external dependencies.

# License
This project is licensed under the terms of the BSD-3-Clause license. Check LICENSE for more info.
