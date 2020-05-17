# Third Party Setup

## Steps

### Common

#### Windows

- Either fire up the Native Tools Command Prompt for Visual Studio or run `vcvars.bat` from a terminal of your choice.
  - Most likely to be located here (year and version may differ)
    - `"C:\Program Files (x86)\Microsoft Visual Studio\<year>\<version>\VC\Auxiliary\Build\vcvars64.bat"`
    - `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"`
- This is to ensure both the compiler (`cl.exe`) and Ninja are added to your path and can be found by `CMake`

#### macOS

- You may need to add `-DCMAKE_C_COMPILER=<path/to/c/compiler> -DCMAKE_CXX_COMPILER=<path/to/c++/compiler>` when running the `CMake` commands if a valid compiler cannot be found by `CMake`.
  - Most likely locations include: `/usr/bin/clang`, `/usr/bin/clang++`, `/usr/local/bin/gcc`, `/usr/local/bin/g++` etc..

### SDL

- Download and unzip [SDL2](https://www.libsdl.org/release/SDL2-2.0.12.zip) to `third-party/libs`
  - e.g. `<root>/third-party/libs/SDL2-2.0.12`
- `cd` to `SDL2` folder
- Run the following commands one after the other

```bash
# build and install SDL2 to third-party/libs/SDL2-2.0.12/install
cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target install
```

### bgfx

- From `third-party/libs`

```bash
mkdir bgfx && cd bgfx
git clone https://github.com/pr0g/bgfx.cmake.git .
git submodule init
git submodule update

# build and install bgfx to third-party/libs/bgfx/install
cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target install
```

### Dear ImGui

- From `third-party/libs`

```bash
# git clone cmakefied to get cmake compatible imgui
mkdir cmakefied && cd cmakefied
git clone https://github.com/pr0g/cmakefied .

# note: If using Windows, for now run this command from the GitBash terminal (to have the .sh script run)
./git-clone.sh imgui
cd ../imgui

# build and install Dear ImGui to third-party/libs/imgui/install
cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target install
```

## Wrap-Up

After downloading/cloning all the projects you can now build the starter application.

If you plan to create several projects you could install these dependencies in a shared location and use `CMAKE_PREFIX_PATH` to point to that location when building.
