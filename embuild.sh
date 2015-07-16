#!/bin/bash

OBJ=src/main.c src/chip8.c src/display.c

emcc -Isrc $OBJ -o web/chip8.js