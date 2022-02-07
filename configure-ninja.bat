@echo off

REM Commands to configure this repo for building after dependencies have been installed

cmake -B build/debug-ninja -G Ninja -DCMAKE_BUILD_TYPE=Debug ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake -B build/release-ninja -G Ninja -DCMAKE_BUILD_TYPE=Release ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
