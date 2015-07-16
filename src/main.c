#include <emscripten/emscripten.h>
#include "media.h"
#include "chip8.h"

void loop() {
	update_machine();

	if (need_redraw){
		draw();
		need_redraw = 0;
	}	
}

int main() {
	if (init_display()) {
		init_machine(NULL);
		emscripten_set_main_loop(loop, 0, 1); // use fixed 60 fps or browser frame rate?
	}
 
	shutdown_display();
 
	return 0;
}