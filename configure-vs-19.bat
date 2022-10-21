@echo off

REM Commands to configure this repo and dependencies for building using the
REM Visual Studio 2019 generator

cmake -B build/vs2019 -G "Visual Studio 16 2019" -A x64 -DSUPERBUILD=ON
