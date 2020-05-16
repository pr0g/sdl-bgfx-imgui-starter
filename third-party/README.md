# third party setup

## steps

- download and unzip [SDL2](https://www.libsdl.org/release/SDL2-2.0.12.zip) to `third-party/libs`
- `cd` to root `SDL2` folder
- if on Windows - `"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"`
- if on macOS add `-DCMAKE_C_COMPILER=<path/to/c/compiler> -DCMAKE_CXX_COMPILER=<path/to/c++/compiler>`
- e.g. `/usr/bin/clang`, `/usr/bin/clang++`, `/usr/local/bin/gcc`, `/usr/local/bin/g++` etc..
- `cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build --target install`
- `cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=RelWithDebInfo`
- `cmake --build build --target install`

- git clone bgfx-cmake to bgfx folder
- `mkdir bgfx && cd bgfx`
- `git clone https://github.com/pr0g/bgfx.cmake.git .`
- `git submodule init`
- `git submodule update`
- `cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build --target install`

- git clone cmakefied to get cmake compatible imgui
- `mkdir cmakefied && cd cmakefied`
- `git clone https://github.com/pr0g/cmakefied .`
- (from git bash prompt on windows or terminal on macOS)
- `./git-clone.sh imgui`
- `cd ../imgui`
- `cmake -S . -B build -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build --target install`
