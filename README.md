# sdl-bgfx-imgui-starter

The idea behind this repo is for it to be used as a minimal starting point for development of a game, demo or experiment.

It utilizes [SDL2](https://www.libsdl.org/index.php) for the windowing system, [bgfx](https://github.com/bkaradzic/bgfx) (by [@bkaradzic](https://twitter.com/bkaradzic)) for the graphics library and [Dear ImGui](https://github.com/ocornut/imgui) (by [@ocornut](https://twitter.com/ocornut)) for the user interface.

The code in `main.cpp` is derived from two excellent `bgfx` tutorials ([hello-bgfx](https://dev.to/pperon/hello-bgfx-4dka) by [Phil Peron](https://twitter.com/pperon) and [bgfx-ubuntu](https://www.sandeepnambiar.com/getting-started-with-bgfx/)) by [Sandeep Nambiar](https://twitter.com/_sandeepnambiar). I highly recommend checking them out!

This repo does not directly include any of these libraries but contains instructions on how to download and install them so this project can use them.

>  __Warning:__ There is a little bit of setup required (please see the prerequisites below) but once you're setup you should be good to go.
>
> In future batch/shell scripts will likely be provided to automate the initial bootstrap.

## Getting Started

Before doing anything else create a directory to hold the repo

```bat
mkdir sdl-bgfx-imgui-starter && cd sdl-bgfx-imgui-starter
```

Then clone the repo

```bash
git clone https://github.com/pr0g/sdl-bgfx-imgui-starter.git .
```

## Prerequisites

Before attempting to build this project all third party dependencies (`SDL`, `bgfx` and `imgui`) must be downloaded and installed. These will be self contained in the repo and are not installed to the system.

To achieve this `CMake` must be installed on your system (repo tested with `3.15`).

Please see the third-party [README](third-party/README.md) for full instructions on how to do this.

> Note: `third-party/libs` is added to the `.gitignore` file to ensure the dependencies aren't added to the project.

## Build Instructions

Once all third party libraries have been downloaded and installed, follow these build instructions to compile the repo (linking to the previously built dependencies).

Shaders for `bgfx` also must be compiled to be loaded by the application. The starter has an incredibly simple shader supporting vertex colours.

> __Info:__ `Ninja` was chosen as the generator for `CMake` as it's consistent across both _macOS_ and _Windows_ (the _Visual Studio/MSVC_ generator supports multiple configurations which is cool but just makes things more complicated when dealing with cross platform commands).
>
> The added benefit of `Ninja` is it also supports creating a `compile_commands.json` file (by providing `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to the `CMake` configure command). This is useful for many different reasons, one of the highlights being offering perfect intellisense for VSCode 😁.
>
> Finally all listed `CMake` configure commands specify `-DCMAKE_BUILD_TYPE=Debug` but when building the dependencies you can also use `Release` or `RelWithDebInfo` to get an optimized build. All dependencies make use of `CMAKE_DEBUG_POSTFIX` which means all built libraries get a '`d`' suffix (the convention) appended, so you can build and install both Debug and Release libraries to the same location.
>
>__Attn:__ If you build the dependencies in `Debug` and then try and build the starter project in `Release` (or vice versa) you're likely to get link errors.

### Windows

#### App - Windows

```bat
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=%cd%/third-party/libs/SDL2-2.0.12/install;%cd%/third-party/libs/bgfx/install;%cd%/third-party/libs/imgui/install -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build
```

#### Shaders - Windows

```bat
third-party\libs\bgfx\install\bin\shaderc.exe -f shader\v_simple.sc -o shader\v_simple.bin --platform windows --type vertex --verbose -i ./ -p vs_5_0

third-party\libs\bgfx\install\bin\shaderc.exe -f shader\f_simple.sc -o shader\f_simple.bin --platform windows --type fragment --verbose -i ./ -p ps_5_0
```

### macOS

#### App - macOS

```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_PREFIX_PATH="$(pwd)/third-party/libs/SDL2-2.0.12/install;$(pwd)/third-party/libs/imgui/install;$(pwd)/third-party/libs/bgfx/install" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build
```

#### Shaders - macOS

```bash
./third-party/libs/bgfx/install/bin/shaderc -f shader/v_simple.sc -o shader/v_simple.bin --platform osx --type vertex --verbose -i ./ -p metal

./third-party/libs/bgfx/install/bin/shaderc -f shader/f_simple.sc -o shader/f_simple.bin --platform osx --type fragment --verbose -i ./ -p metal
```

## Resources

While getting this project setup I discovered a number of excellent resources I'd highly recommend checking them out to learn more about `bgfx` and `Dear ImGui`.

- [bgfx](https://github.com/bkaradzic/bgfx) - `bgfx` main repo
- [bgfx-docs](https://bkaradzic.github.io/bgfx/index.html) - extensive docs covering much of `bgfx`'s API
- [bgfx-cmake](https://github.com/widberg/bgfx.cmake) - a complimentary repo to add CMake support to `bgfx` (used by this repo)
- [hello-bgfx (tutorial)](https://dev.to/pperon/hello-bgfx-4dka) - a great intro to `bgfx` and covers most of the code in the `main.cpp` of this repo
- [bgfx-ubuntu(tutorial)](https://www.sandeepnambiar.com/getting-started-with-bgfx/) - another great tutorial on `bgfx` (showing how to get setup on ubuntu)
- [minimal-bgfx](https://github.com/jpcy/bgfx-minimal-example) - a similar repo to this one only using `premake` and git submodules instead of `CMake` and with no `imgui`.
- [dear-imgui](https://github.com/ocornut/imgui) - `Dear ImGui` main repo - lots of documentation and examples are available there
- [cmakefied](https://github.com/tamaskenez/cmakefied) - a complimentary repo to add CMake support to `imgui` (used by this repo)

## Special Thanks

- [Бранимир Караџић (@bkaradzic)](https://twitter.com/bkaradzic) for the excellent [bgfx](https://github.com/bkaradzic/bgfx)
- [Omar Cornut (@ocornut)](https://twitter.com/ocornut) for the brilliant [Dear Imgui](https://github.com/ocornut/imgui)
- [Widberg/MissingBitStudios](https://github.com/widberg) for the `bgfx` CMake support
- [Tamas Kenez](https://github.com/tamaskenez) for the `Dear Imgui` CMake support
- [Richard Gale (@richardg4)](https://twitter.com/richardg4) for the `bgfx` implementation for `Dear ImGui`
- [Phil Peron (@pperon)](https://twitter.com/pperon) and [Sandeep Nambiar (@_sandeepnambiar)](https://twitter.com/_sandeepnambiar) for the great `bgfx` setup tutorials.
