@echo off
:: disable cygwin temporarily
@set PATH=%PATH:cygwin=cygwin_unused%

set OBJ=src/main.c src/chip8.c src/media.c
set OPT= -s USE_SDL=2 -s EXPORTED_FUNCTIONS="['_main', '_stop_loop']" -O1

emcc -Isrc %OBJ% %OPT% -o web/chip8.js