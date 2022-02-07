@echo off

REM Command to configure this repo for building using the Visual Studio 2019
REM generator (after dependencies have been installed)

cmake -B build/vs2019 -G "Visual Studio 16 2019" -A x64 ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build
