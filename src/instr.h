#ifdef CHIP8_C

/**** INSTRUCTIONS ****/

static inline void instr_00E0(){
	// clear screen
	memset(display, 0, 64*32);
	need_redraw = 1;
}

static inline void instr_00EE(){ 
	// blm RET
}

static inline void instr_1nnn(){ 
	// blm JMP
}

static inline void instr_2nnn(){ 
	// blm CALL
}

static inline void instr_3xkk(){ 
	// blm SE
}

static inline void instr_4xkk(){ 
	// blm SNE
}

static inline void instr_5xy0(){ 
	// blm SE vy
}

static inline void instr_6xkk(){ 
	// blm
}

static inline void instr_7xkk(){ 
	// blm
}

static inline void instr_8xy0(){ 
	// blm
}

static inline void instr_8xy1(){ 
	// blm
}

static inline void instr_8xy2(){ 
	// blm
}

static inline void instr_8xy3(){ 
	// blm
}

static inline void instr_8xy4(){ 
	// blm
}

static inline void instr_8xy5(){ 
	// blm
}

static inline void instr_8xy6(){ 
	// blm
}

static inline void instr_8xy7(){ 
	// blm
}

static inline void instr_8xyE(){ 
	// blm
}

static inline void instr_9xy0(){ 
	// blm
}

static inline void instr_Annn(){ 
	// blm 
}

static inline void instr_Bnnn(){ 
	// blm 
}

static inline void instr_Cxkk(){ 
	// blm 
}

static inline void instr_Dxyn(){ 
	// blm 
}

static inline void instr_Ex9E(){ 
	// blm 
}

static inline void instr_ExA1(){ 
	// blm 
}

static inline void instr_Fx07(){ 
	// blm 
}

static inline void instr_Fx0A(){ 
	// blm 
}

static inline void instr_Fx15(){ 
	// blm 
}

static inline void instr_Fx18(){ 
	// blm 
}

static inline void instr_Fx1E(){ 
	// blm 
}

static inline void instr_Fx29(){ 
	// blm 
}

static inline void instr_Fx33(){ 
	// blm 
}

static inline void instr_Fx55(){ 
	// blm 
}

static inline void instr_Fx65(){ 
	// blm 
}

#endif