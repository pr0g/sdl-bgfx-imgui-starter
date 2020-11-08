# Third Party Setup

## Setup

### Windows

> Note: One of the sub-commands in the third-party `CMakeLists.txt` file requires to be able to run a bash (`.sh`) script.
>
>For this to work please use `GitBash.exe` or [cmder](https://cmder.net/) or some other console emulator, but unfortunately `cmd.exe` won't cut it.

- First run `vcvars.bat` from a terminal of your choice.
  - Most likely to be located here (year and version may differ)
    - `"C:\Program Files (x86)\Microsoft Visual Studio\<year>\<version>\VC\Auxiliary\Build\vcvars64.bat"`
    - e.g. `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"`
- This is to ensure both the compiler (`cl.exe`) and Ninja are added to your path and can be found by `CMake`.

### macOS

- You may need to add `-DCMAKE_C_COMPILER=<path/to/c/compiler> -DCMAKE_CXX_COMPILER=<path/to/c++/compiler>` when running the `CMake` commands if a valid compiler cannot be found by `CMake`.
  - Most likely locations include: `/usr/bin/clang`, `/usr/bin/clang++`, `/usr/local/bin/gcc`, `/usr/local/bin/g++` etc..

## Install

On either Windows or macOS, `cd` to the `third-party` folder and run:

```cmake
cmake -S . -B build
```

It's fine not to specify a generator, any should work (and the `CMakeLists.txt` file should handle either single or multi-config generators).

Then run:

```cmake
cmake --build build
```

It might take a little while but behind the scenes `CMake` will go away and download, configure, build and install `SDL`, `bgfx` and `Dear ImGui`.

Once everything is complete you should be able to continue with the instructions in the main [README](README.md).

## Wrap-Up

If you plan to create several projects you could install these dependencies in a shared location and use `CMAKE_PREFIX_PATH` to point to that location when building.

All dependencies make use of `CMAKE_DEBUG_POSTFIX` which means all built libraries get a '`d`' suffix (the convention) appended, so both Debug and Release libraries are installed to the same location.
