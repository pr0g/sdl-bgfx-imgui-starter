#!/bin/bash

# Commands to configure this repo and dependencies for building

cmake -B build/debug-make -G "Unix Makefiles" \
-DCMAKE_BUILD_TYPE=Debug -DSUPERBUILD=ON

cmake -B build/release-make -G "Unix Makefiles" \
-DCMAKE_BUILD_TYPE=Release -DSUPERBUILD=ON
