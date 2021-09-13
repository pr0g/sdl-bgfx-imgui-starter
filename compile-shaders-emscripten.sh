#!/bin/bash

# compile shaders

# simple shader
./third-party/build/bin/shaderc \
-f shader/v_simple.sc -o shader/v_simple.bin \
--platform asmjs --type vertex --verbose -i ./

./third-party/build/bin/shaderc \
-f shader/f_simple.sc -o shader/f_simple.bin \
--platform asmjs --type fragment --verbose -i ./
