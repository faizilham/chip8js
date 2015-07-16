#include <emscripten/emscripten.h>
#include "display.h"


void main_loop() {
	draw();
}

int main() {
	if (init_display()) {
		emscripten_set_main_loop(main_loop, 60, 1);
	}
 
	shutdown_display();
 
	return 0;
}