# sdl-bgfx-imgui-starter

![starter](starter.png)

The idea behind this repo is for it to be used as a minimal starting point for development of a game, demo or experiment.

It utilizes [SDL2](https://www.libsdl.org/index.php) for the windowing system, [bgfx](https://github.com/bkaradzic/bgfx) (by [@bkaradzic](https://twitter.com/bkaradzic)) for the graphics library and [Dear ImGui](https://github.com/ocornut/imgui) (by [@ocornut](https://twitter.com/ocornut)) for the user interface.

The code in `main.cpp` is derived from two excellent `bgfx` tutorials ([hello-bgfx](https://dev.to/pperon/hello-bgfx-4dka) by [Phil Peron](https://twitter.com/pperon) and [bgfx-ubuntu](https://www.sandeepnambiar.com/getting-started-with-bgfx/) by [Sandeep Nambiar](https://twitter.com/_sandeepnambiar)). I highly recommend checking them out!

This repo does not directly include any of these libraries but contains ~~instructions on how to download and install them~~ _a CMake script to download and install them_ so this project can use them.

>__Warning:__ There is a little bit of setup required. Please see the prerequisites below.

## Prerequisites

To begin with create a directory to hold the repo:

```bat
mkdir sdl-bgfx-imgui-starter && cd sdl-bgfx-imgui-starter
```

Then clone the repo:

```bash
git clone https://github.com/pr0g/sdl-bgfx-imgui-starter.git .
```

Before attempting to build this project __all third party dependencies__ (`SDL`, `bgfx` and `imgui`) must be __downloaded and installed__ (CMake now takes care of this with `ExternalProject_Add`). To achieve this `CMake` must be installed on your system (repo tested with CMake version `3.15`).

> Note: The libraries are self contained in the repo and are not installed to the system.

Please see the third-party [__README__](third-party/README.md) for full instructions on how to do this.

> Do __not__ proceed to __Build Instructions__ until you've done this.

## Build Instructions

Once all third party libraries have been downloaded and installed, follow these build instructions to compile the repo.

Shaders for `bgfx` also must be compiled to be loaded by the application (the starter has an incredibly simple shader supporting vertex colours).

> __Info:__ A `configure.bat` and `configure.sh` file are provided (mainly as an exmaple) to run the CMake configure commands. `Ninja` was chosen as the generator for these as it's consistent across both _macOS_ and _Windows_, any generator should work though. There's also `configure-vs.bat` for generating a Visual Studio solution.

### Windows

- Run `./configure.bat` located in the root directory to generate the build files required for the project.
- Run `cmake --build build/debug` and/or `cmake --build build/release` to compile the project.
- Run `./compile-shaders.bat` located in the root directory to build the shaders.
- Launch the application by running `./build/debug/sdl-bgfx-imgui-starter` or `./build/release/sdl-bgfx-imgui-starter`.

### macOS

- Run `./configure.sh` located in the root directory to generate the build files required for the project.
- Run `cmake --build build/debug` and/or `cmake --build build/release` to compile the project.
- Run `./compile-shaders.sh` located in the root directory to build the shaders.
- Launch the application by running `build\debug\sdl-bgfx-imgui-starter.exe` or `build\release\sdl-bgfx-imgui-starter.exe`.

## Resources

While getting this project setup I discovered a number of excellent resources. I'd highly recommend checking them out to learn more about `bgfx` and `Dear ImGui`.

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
