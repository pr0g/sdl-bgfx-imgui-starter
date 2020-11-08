@echo off

REM Command to configure this repo for building after dependencies have been installed

cmake -S . -B build-vs -G "Visual Studio 16 2019" -A x64 ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build
