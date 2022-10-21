@echo off

REM Commands to configure this repo and dependencies for building

call emcmake cmake -B build/debug-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON

call emcmake cmake -B build/release-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Release-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON
