#ifndef chip8_h
#define chip8_h

void init_machine(char* rom_file);
void update_machine();
extern int need_redraw;
extern int wait_key;
extern int sound_playing;
extern int st;


#endif