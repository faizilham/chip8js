#ifndef media_h
#define media_h
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef unsigned char byte;
#define ANY_KEY 0xFF

extern char display[64][32];

int init_display();
void shutdown_display();
void draw();
void poll_keyevent();
int key_pressed(byte key);
byte get_pressed();

#endif