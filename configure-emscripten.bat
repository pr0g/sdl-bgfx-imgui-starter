@echo off

emcmake cmake -S . -B build/emscripten -G Ninja ^
-DCMAKE_PREFIX_PATH=%cd%/third-party/build
