@echo off

REM Command to configure this repo for building using the Visual Studio 2022
REM generator (after dependencies have been installed)

cmake -B build/vs2022 -G "Visual Studio 17 2022" -A x64 ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build
