@echo off
:: disable cygwin temporarily
@set PATH=%PATH:cygwin=cygwin_unused%

:: notes, 02 and 03 optimization not working
set OBJ=src/main.c src/chip8.c src/media.c
set OPT= -s USE_SDL=2 -s EXPORTED_FUNCTIONS="['_main', '_stop_loop']" -O1 --embed-file beep.wav

emcc -Isrc %OBJ% %OPT% -o web/chip8.js