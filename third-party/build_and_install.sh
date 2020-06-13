#!/bin/bash

cmake -S . -B build/debug -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B build/release -G Ninja -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build/debug --target install
cmake --build build/release --target install
