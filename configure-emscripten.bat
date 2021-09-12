@echo off

REM Commands to configure this repo for building after dependencies have been installed

emcmake cmake -S . -B build/debug-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Debug ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build

emcmake cmake -S . -B build/release-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Release ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build
