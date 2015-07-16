#!/bin/bash

OBJ=src/main.c src/chip8.c src/media.c

emcc -Isrc $OBJ -s USE_SDL=2 -o web/chip8.js