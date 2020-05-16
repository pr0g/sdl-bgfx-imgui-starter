# sdl-bgfx-imgui-starter

## prerequisites

- Download and install all third party dependencies (see [third-party/README.md](third-party/README.md))

## build instructions

- `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="%cd%/third-party/libs/SDL2-2.0.12/install";"%cd%/third-party/libs/bgfx/install";"%cd%/third-party/libs/imgui/install" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_PREFIX_PATH="%cd%/third-party/libs/SDL2-2.0.12/install";"%cd%/third-party/libs/bgfx/install";"%cd%/third-party/libs/imgui/install" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`

- `third-party\libs\bgfx\install\bin\shaderc.exe -f shader\v_simple.sc -o shader\v_simple.bin --platform windows --type vertex --verbose -i ./ -p vs_5_0`
- `third-party\libs\bgfx\install\bin\shaderc.exe -f shader\f_simple.sc -o shader\f_simple.bin --platform windows --type fragment --verbose -i ./ -p ps_5_0`

- `cmake --build build`

## resources

- [bgfx](https://github.com/bkaradzic/bgfx)
- [bgfx-docs](https://bkaradzic.github.io/bgfx/index.html)
- [bgfx-cmake](https://github.com/widberg/bgfx.cmake)
- [cmakefied](https://github.com/tamaskenez/cmakefied)
- [dear-imgui](https://github.com/ocornut/imgui)
- [hello-bgfx (tutorial)](https://dev.to/pperon/hello-bgfx-4dka)
- [bgfx-ubuntu(tutorial)](https://www.sandeepnambiar.com/getting-started-with-bgfx/)
- [minimal-bgfx](https://github.com/jpcy/bgfx-minimal-example)
