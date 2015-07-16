@echo off
:: disable cygwin temporarily
@set PATH=%PATH:cygwin=cygwin_unused%

set OBJ=src/main.c src/chip8.c src/display.c

emcc -Isrc %OBJ% -o web/chip8.html