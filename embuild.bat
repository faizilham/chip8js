@echo off
:: disable cygwin temporarily
@set PATH=%PATH:cygwin=cygwin_unused%

set OBJ=src/main.c src/chip8.c src/display.c

emcc -Isrc %OBJ% -s USE_SDL=2 -o web/chip8.js