@echo off

REM Commands to configure this repo and dependencies for building

cmake -B build/debug-ninja -G Ninja -DCMAKE_BUILD_TYPE=Debug -DSUPERBUILD=ON

cmake -B build/release-ninja -G Ninja -DCMAKE_BUILD_TYPE=Release -DSUPERBUILD=ON
