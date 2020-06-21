aur
===

*aur* is a simple C++ creative coding and visualization library.

## Prerequisites

* Conan (version `1.26.0` or higher)
* CMake (version `3.10.2` or higher)
* MSVC, Clang, GCC (any version with support of C++17)
* GPU drivers (latest version with stable support of OpenGL ES 2.0)

## Building

Create a `build` directory and set it as a current working directory:

```bash
mkdir build
cd build
```

Install dependencies with the Conan package manager:

```bash
conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
conan install .. --build sdl2_image --build sdl2_mixer
```

Configure the project to generate IDE or Makefiles:

```bash
# On Windows for Visual Studio
cmake .. -G "Visual Studio 16 2019"

# On macOS for Xcode
cmake .. -G "Xcode"

# on macOS or GNU/Linux to generate Makefiles
cmake .. -G "Unix Makefiles"
```

Build the project:

```bash
cmake --build .
```

Run the test program from the `aur/build/bin/` directory:

```bash
cd .. # Ensure that the current working directory is set to the root aur folder.
./build/bin/<name of the graphics test executable>
```

## Credits

*aur* was created by [Dmitrii Toksaitov](https://github.com/toksaitov).
