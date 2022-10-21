#!/bin/bash

# Commands to configure this repo and dependencies for building

cmake -B build/debug-make -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON

cmake -B build/release-make -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON
