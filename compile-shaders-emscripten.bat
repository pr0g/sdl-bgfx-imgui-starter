@echo off

REM compile shaders

REM simple shader
third-party\build\bin\shaderc.exe ^
-f shader\v_simple.sc -o shader\embuild\v_simple.bin ^
--platform asmjs --type vertex --verbose -i ./

third-party\build\bin\shaderc.exe ^
-f shader\f_simple.sc -o shader\embuild\f_simple.bin ^
--platform asmjs --type fragment --verbose -i ./
