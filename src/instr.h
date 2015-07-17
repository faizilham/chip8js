#ifdef CHIP8_C

/**** Digit Sprites ****/

byte digit_sprite[80] = {0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0, 0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0, 0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80};

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
	reg[0xF] = (reg[get2()] & 0x80) ? 1 : 0;
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
	// Vx = random(256) & kk
	reg[get2()] = (rand() % 256) & get_kk();
}

static inline void instr_Dxyn(){ 
	// draw sprite

	int x1 = reg[get2()], y1 = reg[get3()], n = get4(), vf = 0, mask;
	byte row, px, pold;
	for (int y = 0; y < n; ++y){
		row = mem[reg_i + y];
		mask = 0x80;
		for (int x = 0; x < 8; ++x){
			px = (row & mask) ? 1 : 0; mask >>=1; // translate to display pixel for each bit
			display[x1 + x][y1 + y] ^= px; // xor the sprite to current screen

			vf |= px && !display[x1 + x][y1 + y]; // check erased: pixel is 1 and result is 0
		}
	}

	need_redraw = 1;
}

static inline void instr_Ex9E(){ 
	// skip if key == Vx pressed
	if (key_pressed(reg[get2()])) pc += 2;
}

static inline void instr_ExA1(){ 
	// skip if key == Vx not pressed
	if (!key_pressed(reg[get2()])) pc += 2;
}

static inline void instr_Fx07(){ 
	// Vx = DT
	reg[get2()] = dt;
}

static inline void instr_Fx0A(){ 
	// wait until key pressed then Vx = key
	if (key_pressed(ANY_KEY)){
		wait_key = 0;
		reg[get2()] = get_pressed();
	}else{
		wait_key = 1;
		pc -= 2;
	}
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
	// I = location of sprite for digit Vx.
	reg_i = 5 * reg[get2()];
}

static inline void instr_Fx33(){ 
	// BCD representation of Vx in memory locations I, I+1, and I+2
	int vx = reg[get2()];
	for (int i = 2; i >= 0; --i){
		mem[reg_i + i] = vx % 10;
		vx = vx / 10;
	}
}

static inline void instr_Fx55(){ 
	// store registers to mem[I] until mem[I+x]
	int x = get2();
	for (int i = 0; i <= x; ++i) mem[reg_i + i] = reg[i];
}

static inline void instr_Fx65(){ 
	// read registers from mem[I] until mem[I+x] 
	int x = get2();
	for (int i = 0; i <= x; ++i) reg[i] = mem[reg_i + i];
}

#endif