# sdl-bgfx-imgui-starter

## Prerequisites

- Download and install all third party dependencies (see [third-party/README.md](third-party/README.md) for instructions).

## Build Instructions

### Windows app

- `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="%cd%/third-party/libs/SDL2-2.0.12/install";"%cd%/third-party/libs/bgfx/install";"%cd%/third-party/libs/imgui/install" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`

### macOS app

- `cmake -S . -B build -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_PREFIX_PATH="$(pwd)/third-party/libs/SDL2-2.0.12/install;$(pwd)/third-party/libs/imgui/install;$(pwd)/third-party/libs/bgfx/install"`

- `cmake --build build`

### Windows shaders

- `third-party\libs\bgfx\install\bin\shaderc.exe -f shader\v_simple.sc -o shader\v_simple.bin --platform windows --type vertex --verbose -i ./ -p vs_5_0`

- `third-party\libs\bgfx\install\bin\shaderc.exe -f shader\f_simple.sc -o shader\f_simple.bin --platform windows --type fragment --verbose -i ./ -p ps_5_0`

### macOS shaders

- `./third-party/libs/bgfx/install/bin/shaderc -f shader/v_simple.sc -o shader/v_simple.bin --platform osx --type vertex --verbose -i ./ -p metal`
- `./third-party/libs/bgfx/install/bin/shaderc -f shader/f_simple.sc -o shader/f_simple.bin --platform osx --type fragment --verbose -i ./ -p metal`

## Resources

- [bgfx](https://github.com/bkaradzic/bgfx)
- [bgfx-docs](https://bkaradzic.github.io/bgfx/index.html)
- [bgfx-cmake](https://github.com/widberg/bgfx.cmake)
- [cmakefied](https://github.com/tamaskenez/cmakefied)
- [dear-imgui](https://github.com/ocornut/imgui)
- [hello-bgfx (tutorial)](https://dev.to/pperon/hello-bgfx-4dka)
- [bgfx-ubuntu(tutorial)](https://www.sandeepnambiar.com/getting-started-with-bgfx/)
- [minimal-bgfx](https://github.com/jpcy/bgfx-minimal-example)
