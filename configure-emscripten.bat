@echo off

REM Commands to configure this repo and dependencies for building

call emcmake cmake -B embuild/debug-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Debug -DSUPERBUILD=ON

call emcmake cmake -B embuild/release-emscripten -G Ninja ^
-DCMAKE_BUILD_TYPE=Release -DSUPERBUILD=ON
