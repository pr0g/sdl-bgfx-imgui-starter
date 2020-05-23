@echo off

REM command to configure this repo for building after dependencies have been installed
cmake -S . -B build-vs -G "Visual Studio 16 2019" -A x64 ^
-DCMAKE_PREFIX_PATH=^
%cd%/third-party/libs/SDL2-2.0.12/install;^
%cd%/third-party/libs/bgfx/install;^
%cd%/third-party/libs/imgui/install
