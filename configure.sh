#!/bin/bash

# Commands to configure this repo for building after dependencies have been installed

cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_PREFIX_PATH=\
"$(pwd)/third-party/libs/SDL2-2.0.12/install;\
$(pwd)/third-party/libs/bgfx/install;\
$(pwd)/third-party/libs/imgui/install" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake -S . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo \
-DCMAKE_PREFIX_PATH=\
"$(pwd)/third-party/libs/SDL2-2.0.12/install;\
$(pwd)/third-party/libs/bgfx/install;\
$(pwd)/third-party/libs/imgui/install" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
