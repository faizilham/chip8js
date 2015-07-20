#include <emscripten/emscripten.h>
#include "media.h"
#include "chip8.h"

void stop_loop(){
	emscripten_cancel_main_loop();
	shutdown_media();
}

void loop() {
	poll_keyevent();
	update_machine();

	if (need_redraw){
		draw();
		need_redraw = 0;
	}
}

int main() {
	if (init_media()) {
		init_machine("/temp.rom");
		emscripten_set_main_loop(loop, 60, 1); // use fixed 60 fps or browser frame rate?
	}
 
	shutdown_media();
 
	return 0;
}