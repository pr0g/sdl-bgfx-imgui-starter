@echo off

fd -0 -e h -e cpp -a | xargs -0 clang-format -i
