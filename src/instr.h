#ifdef CHIP8_C

/**** INSTRUCTIONS ****/

static inline void instr_00E0(){
	// clear screen
	memset(display, 0, 64*32);
	need_redraw = 1;
}

static inline void instr_00EE(){ 
	// RET
	pc = stack[sp--];
}

static inline void instr_1nnn(){ 
	// jump to nnn
	pc = get_nnn();
}

static inline void instr_2nnn(){ 
	// CALL at nnn
	stack[++sp] = pc;
	pc = get_nnn();
}

static inline void instr_3xkk(){ 
	// skip next if Vx == kk
	if (reg[get2()] == get_kk()) pc += 2;
}

static inline void instr_4xkk(){ 
	// skip next if Vx != kk
	if (reg[get2()] != get_kk()) pc += 2;
}

static inline void instr_5xy0(){ 
	// skip next if Vx == Vy
	if (reg[get2()] == reg[get3()]) pc += 2;
}

static inline void instr_6xkk(){ 
	// Set Vx = KK
	reg[get2()] = get_kk();
}

static inline void instr_7xkk(){ 
	// Vx += kk
	reg[get2()] += get_kk();
}

static inline void instr_8xy0(){ 
	// Vx = Vy
	reg[get2()] = reg[get3()];
}

static inline void instr_8xy1(){ 
	// Vx |= Vy
	reg[get2()] |= reg[get3()];
}

static inline void instr_8xy2(){ 
	// Vx &= Vy
	reg[get2()] &= reg[get3()];
}

static inline void instr_8xy3(){ 
	// Vx ^= Vy
	reg[get2()] ^= reg[get3()];
}

static inline void instr_8xy4(){
	// Vx = Vx + Vy, VF = carry.
	int temp = reg[get2()] + reg[get3()];

	reg[get2()] = temp & 0xFF;
	reg[0xF] = temp > 255 ? 1 : 0;
}

static inline void instr_8xy5(){ 
	// Vx = Vx - Vy, VF = NOT borrow.
	reg[0xF] = reg[get2()] > reg[get3()] ? 1 : 0;
	reg[get2()] -= reg[get3()];
}

static inline void instr_8xy6(){ 
	// Vx = Vx >> 1. VF = last bit
	reg[0xF] = reg[get2()] & 0x01;
	reg[get2()] >>= 1;
}

static inline void instr_8xy7(){ 
	// Vx = Vy - Vx, VF = NOT borrow.
	reg[0xF] = reg[get2()] < reg[get3()] ? 1 : 0;
	reg[get2()] = reg[get3()] - reg[get2()];
}

static inline void instr_8xyE(){ 
	// Vx = Vx << 1. VF = first bit
	reg[0xF] = reg[get2()] & 0x80;
	reg[get2()] <<= 1;
}

static inline void instr_9xy0(){ 
	// skip next if Vx != Vy
	if (reg[get2()] != reg[get3()]) pc += 2;
}

static inline void instr_Annn(){ 
	// I = nnn
	reg_i = get_nnn();
}

static inline void instr_Bnnn(){ 
	// jump to V0 + nnn
	pc = reg[0] + get_nnn();
}

static inline void instr_Cxkk(){ 
	// blm, random
}

static inline void instr_Dxyn(){ 
	// blm, draw
}

static inline void instr_Ex9E(){ 
	// blm 
}

static inline void instr_ExA1(){ 
	// blm 
}

static inline void instr_Fx07(){ 
	// Vx = DT
	reg[get2()] = dt;
}

static inline void instr_Fx0A(){ 
	// blm 
}

static inline void instr_Fx15(){ 
	// dt = Vx
	dt = reg[get2()];
}

static inline void instr_Fx18(){ 
	// st = Vx
	st = reg[get2()];
}

static inline void instr_Fx1E(){ 
	// I = I + Vx.
	reg_i += reg[get2()];
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