@echo off

REM Commands to configure this repo and dependencies for building using the
REM Visual Studio 2022 generator

cmake -B build/vs2022 -G "Visual Studio 17 2022" -A x64 -DSUPERBUILD=ON
