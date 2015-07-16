#ifndef chip8_h
#define chip8_h

void init_machine(char* rom_file);
void update_machine();
extern int need_redraw;


#endif