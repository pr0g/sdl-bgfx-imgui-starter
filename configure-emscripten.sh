#!/bin/bash

# Commands to configure this repo and dependencies for building

emcmake cmake -B build/debug-emscripten -G Ninja -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON

emcmake cmake -B build/release-emscripten -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSUPERBUILD=ON
