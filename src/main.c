#include <emscripten/emscripten.h>
#include "media.h"
#include "chip8.h"

static int last_tick;

void stop_loop(){
	emscripten_cancel_main_loop();
	shutdown_media();
}

void trigger_stop(){
	printf("machine halted\n");
	EM_ASM(notify_stop());
	emscripten_pause_main_loop();
}

void loop() {
	int start_tick = SDL_GetTicks();
	int elapsed =  start_tick - last_tick;
	poll_keyevent();
	update_machine(elapsed * 600 / 1000);

	if (need_redraw){
		draw();
		need_redraw = 0;

		render_screen();
	}


	last_tick = start_tick;
}

int main() {
	if (init_media()) {
		init_machine("/temp.rom", trigger_stop);
		last_tick = SDL_GetTicks();
		emscripten_set_main_loop(loop, 60, 1); // use fixed 60 fps or browser frame rate?
	}
 
	shutdown_media();
 
	return 0;
}