# Third Party Setup

> __Note__: _Nearly_ all steps listed here are now optional and are not required thanks to the new _superbuild_ CMake script and option (`-DSUPERBUILD=ON`) supported by the repository.
>
>All third party dependencies will be automatically downloaded and built as part of the normal configuration process (see instructions in the main [__README__](/README.md) and accompanying configure scripts for details).

## Setup

### Windows

- First run `VsDevCmd.bat` from a terminal of your choice.
  - Most likely to be located here (year and version may differ).
    - `"C:\Program Files\Microsoft Visual Studio\<year>\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64`
    - e.g. `"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64`
    - _Note:_ `-arch=x64 -host_arch=x64` are required for `x86_64` otherwise `x86` (32bit) is used as the default.
- This is to ensure both the compiler (`cl.exe`) and Ninja are added to your path and can be found by CMake.

### macOS

- You may need to add `-DCMAKE_C_COMPILER=<path/to/c/compiler> -DCMAKE_CXX_COMPILER=<path/to/c++/compiler>` when running the CMake commands if a valid compiler cannot be found by CMake.
  - Most likely locations include: `/usr/bin/clang`, `/usr/bin/clang++`, `/usr/local/bin/gcc`, `/usr/local/bin/g++` etc...

### Linux

- You may need to install a few libraries before the third party dependencies can be built (most notably OpenGL and X11 if they're not already on your system). You'll likely get CMake configure errors if you're missing them.

```bash
# suggested command

sudo apt-get install libx11-dev libglu1-mesa-dev libgl1-mesa-glx libxext-dev ninja-build
```

- ... to get X11, OpenGL, GLX and Ninja

## Install

On either Windows, macOS or Linux, `cd` to the `third-party` folder and run:

```cmake
cmake -B build
```

It's fine not to specify a generator, any should work (and the `CMakeLists.txt` file should handle either single or multi-config generators).

> Note: For single-config generators the above will configure the libraries to build in `Debug`. To build them in `Release` (after performing the step listed below to build the libraries in `Debug`), run `cmake -B build -DCMAKE_BUILD_TYPE=Release`, and then invoke `cmake --build build` again.

Then run:

```cmake
cmake --build build
```

> Note: For single-config generators (`Make`, `Ninja`) this will build the configuration provided by `-DCMAKE_BUILD_TYPE` (`Debug` by default if omitted). For multi-config generators (e.g. Visual Studio) `cmake --build build` will by default build the `Debug` configuration. To build `Release`, use `cmake --build build --config Release`.

It might take a little while but behind the scenes CMake will go away and download, configure, build and install `SDL`, `bgfx` and `Dear ImGui`.

Once everything is complete you should be able to continue with the instructions in the main [README](README.md).

## Emscripten

It's possible to build the third party dependencies for use with Emscripten. To do this run the same commands as before, only prefix the configure step with `emcmake`. It's recommended to use `embuild` as the build folder to stop Emscripten overwriting the native build that may already exist.

```bash
# install emsdk (instructions: https://emscripten.org/docs/getting_started/downloads.html)
# setup Emscripten environment variables
source <emsdk>/emsdk_env.sh # on macOS/Linux
# or
<emsdk>/emsdk_env.bat # on Windows
#
emcmake cmake -B embuild # configure for Emscripten
cmake --build embuild # build libraries for Emscripten
```

## Wrap-Up

If you plan to create several projects you could install these dependencies to a shared location and use `CMAKE_PREFIX_PATH` to point to that location when building.

All dependencies make use of `CMAKE_DEBUG_POSTFIX` which means all built debug libraries get a '`d`' suffix (the convention) appended, so both Debug and Release libraries are installed to the same location.
