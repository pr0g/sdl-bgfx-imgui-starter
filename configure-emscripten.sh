#!/bin/bash

# Commands to configure this repo and dependencies for building

emcmake cmake -B embuild/debug-emscripten -G Ninja \
-DCMAKE_BUILD_TYPE=Debug -DSUPERBUILD=ON

emcmake cmake -B embuild/release-emscripten -G Ninja \
-DCMAKE_BUILD_TYPE=Release -DSUPERBUILD=ON
