@echo off

REM command to configure this repo for building after dependencies have been installed
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug ^
-DCMAKE_PREFIX_PATH=^
%cd%/third-party/libs/SDL2-2.0.12/install;^
%cd%/third-party/libs/bgfx/install;^
%cd%/third-party/libs/imgui/install ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
