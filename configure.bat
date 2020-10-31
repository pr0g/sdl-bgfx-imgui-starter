@echo off

REM Commands to configure this repo for building after dependencies have been installed

cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake -S . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
