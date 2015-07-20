#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chip8.h"
#include "media.h"
#include <time.h>
#define CHIP8_C

#define PROGRAM_START 0x200
#define MEMORY_SIZE 4096
#define MAX_PROGRAM_SIZE 3584

byte mem[MEMORY_SIZE];
byte reg[16];
int reg_i;
int pc, sp, dt, st;
int need_redraw;
int stack[16];
byte code1, code2;

// machine states
int machine_stop;
int wait_key;
int sound_playing;

/*** Instruction Codes Byte Reading Function ***/
static inline byte get1(){
	return (code1 >> 4) & 0x0F;
}

static inline byte get2(){
	return code1 & 0x0F;
}

static inline byte get3(){
	return (code2 >> 4) & 0x0F;
}

static inline byte get4(){
	return code2 & 0x0F;
}

static inline byte get_kk(){
	return code2 & 0xFF;
}

static inline int get_nnn(){
	int ret = get2();
	return (ret << 8) | get_kk();
}

/*** Include: Chip8 Instruction Codes ***/
#include "instr.h"

void init_machine(char* rom_file){
	printf("machine starts\n");
	memset(mem, 0, MEMORY_SIZE);

	// init machine state
	pc = PROGRAM_START; sp = -1; dt = 0; st = 0; need_redraw = 1; machine_stop = 0; sound_playing = 0;
	wait_key = 0;
	srand(time(NULL));

	// copy digits
	memcpy(mem, digit_sprite, 80);

	// read rom
	FILE *file = NULL; char buf[1024];
	if ((file = fopen(rom_file, "rb")) != NULL){
		printf("reading rom file\n");		

		// get size
		fseek(file, 0L, SEEK_END);
		int size = ftell(file);
		printf("size: %d\n", size);
		rewind(file);

		// read file
		if (size < MAX_PROGRAM_SIZE){
			int sz = fread(mem + pc, size, 1, file);
			printf("read: %d\n", sz);
		}
		fclose(file);
	}	
}

static inline void execute_one(){
	// fetch opcode
	code1 = mem[pc]; code2 = mem[pc+1];
	pc+=2;
	
	byte front = get1(); int temp;
	switch(front){
		case 0x0:{
			temp = get_kk();
			if (temp == 0xE0){
				instr_00E0();	
			}else if (temp == 0xEE){
				instr_00EE();
			}else{

			}
			
			// 0nnn not implemented
		} break;

		case 0x1: instr_1nnn(); break;
		case 0x2: instr_2nnn(); break;
		case 0x3: instr_3xkk(); break;
		case 0x4: instr_4xkk(); break;
		case 0x5: instr_5xy0(); break;
		case 0x6: instr_6xkk(); break;
		case 0x7: instr_7xkk(); break;

		case 0x8:{
			temp = get4();

			switch(temp){
				case 0x0: instr_8xy0(); break;
				case 0x1: instr_8xy1(); break;
				case 0x2: instr_8xy2(); break;
				case 0x3: instr_8xy3(); break;
				case 0x4: instr_8xy4(); break;
				case 0x5: instr_8xy5(); break;
				case 0x6: instr_8xy6(); break;
				case 0x7: instr_8xy7(); break;
				case 0xE: instr_8xyE(); break;
				default: break;
			}
		} break;


		case 0x9: instr_9xy0(); break;
		case 0xA: instr_Annn(); break;
		case 0xB: instr_Bnnn(); break;
		case 0xC: instr_Cxkk(); break;
		case 0xD: instr_Dxyn(); break;

		case 0xE:{
			temp = get_kk();
			if (temp == 0x9E){
				instr_Ex9E();
			}else if (temp == 0xA1){
				instr_ExA1();
			}else{

			}
		} break;

		case 0xF:{
			temp = get_kk();
			switch (temp){
				case 0x07: instr_Fx07(); break;
				case 0x0A: instr_Fx0A(); break;
				case 0x15: instr_Fx15(); break;
				case 0x18: instr_Fx18(); break;
				case 0x1E: instr_Fx1E(); break;
				case 0x29: instr_Fx29(); break;
				case 0x33: instr_Fx33(); break;
				case 0x55: instr_Fx55(); break;
				case 0x65: instr_Fx65(); break;
				default: break;
			}
		} break;

		default: break;
	}

	if (pc >= MEMORY_SIZE) machine_stop = 1;
}

void update_machine(){
	// update timer
	if (dt > 0) --dt;

	if (st > 0) {
		--st;
	} else if (sound_playing) {
		sound_playing = 0;
		end_bell();
	}

	int temp_sound_playing = sound_playing;
	// update
	for (int i = 0; i < 10 && temp_sound_playing == sound_playing; ++i)
		execute_one();
}