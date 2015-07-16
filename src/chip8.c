#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chip8.h"
#include "display.h"
#define CHIP8_C

byte mem[4096];
byte reg[16];
int reg_i;
int pc;
int need_redraw = 1;

/*** Instruction Codes Byte Reading Function ***/
static inline byte get1(){
	return mem[pc] & 0xF0;
}

static inline byte get2(){
	return mem[pc] & 0x0F;
}

static inline byte get3(){
	return mem[pc+1] & 0xF0;
}

static inline byte get4(){
	return mem[pc+1] & 0x0F;
}

static inline byte get_kk(){
	return mem[pc+1] & 0xFF;
}

static inline int get_nnn(){
	int ret = get1();
	return (ret << 8) | get_kk();
}

/*** Include: Chip8 Instruction Codes ***/
#include "instr.h"

void init_machine(char* rom_file){
	// read rom

	//
	pc = 0x200;
}

void update_machine(){
	// update timer
	// update 
}


inline void execute_one(){
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
	
	pc+=2;
}