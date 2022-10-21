@echo off

REM Commands to configure this repo and dependencies for building

cmake -B build/debug-ninja -G Ninja -DCMAKE_BUILD_TYPE=Debug ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON

cmake -B build/release-ninja -G Ninja -DCMAKE_BUILD_TYPE=Release ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON
