#ifndef display_h
#define display_h
#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>

int init_gl();
void shutdown_gl();

void on_surface_created();
void on_surface_changed();
void draw();

#endif