#include <emscripten/emscripten.h>
#include "display.h"


void do_frame() {
	draw();
}

int main() {
	if (init_gl() == GL_TRUE) {
		on_surface_created();
		on_surface_changed();
		emscripten_set_main_loop(do_frame, 24, 1);
	}
 
	shutdown_gl();
 
	return 0;
}