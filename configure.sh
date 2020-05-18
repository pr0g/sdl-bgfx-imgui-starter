#!/bin/bash

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_PREFIX_PATH=\
"$(pwd)/third-party/libs/SDL2-2.0.12/install;\
$(pwd)/third-party/libs/bgfx/install;\
$(pwd)/third-party/libs/imgui/install" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
