@echo off

REM compile shaders

if not exist shader\build mkdir shader\build

REM simple shader
third-party\build\bin\shaderc.exe ^
-f shader\v_simple.sc -o shader\build\v_simple.bin ^
--platform windows --type vertex --verbose -i ./ -p s_5_0

third-party\build\bin\shaderc.exe ^
-f shader\f_simple.sc -o shader\build\f_simple.bin ^
--platform windows --type fragment --verbose -i ./ -p s_5_0
