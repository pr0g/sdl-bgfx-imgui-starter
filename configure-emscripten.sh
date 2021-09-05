#!/bin/bash

# Commands to configure this repo for building after dependencies have been installed

emcmake cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_PREFIX_PATH="$(pwd)/third-party/build"

emcmake cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_PREFIX_PATH="$(pwd)/third-party/build"
