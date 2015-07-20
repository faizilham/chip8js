#ifndef media_h
#define media_h
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef unsigned char byte;
#define ANY_KEY 0xFF

extern char display[64][32];

int init_media();
void shutdown_media();
void draw();
void poll_keyevent();
int key_pressed(byte key);
byte get_pressed();

void start_bell();
void end_bell();
void push_audio_buffer();

#endif