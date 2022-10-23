#!/bin/bash

# compile shaders

mkdir -p shader/build

# simple shader
./third-party/build/bin/shaderc \
-f shader/v_simple.sc -o shader/build/v_simple.bin \
--platform linux --type vertex --verbose -i ./ -p spirv

./third-party/build/bin/shaderc \
-f shader/f_simple.sc -o shader/build/f_simple.bin \
--platform linux --type fragment --verbose -i ./ -p spirv
