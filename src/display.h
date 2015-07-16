#ifndef display_h
#define display_h
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

extern char display[64][32];

int init_display();
void shutdown_display();
void draw();

#endif