#!/bin/bash

# compile shaders

# simple shader
./third-party/build/bin/shaderc \
-f shader/v_simple.sc -o shader/v_simple.bin \
--platform osx --type vertex --verbose -i ./ -p metal

./third-party/build/bin/shaderc \
-f shader/f_simple.sc -o shader/f_simple.bin \
--platform osx --type fragment --verbose -i ./ -p metal
