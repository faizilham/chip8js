#include "display.h"

int init_gl(){
	const int width = 640, height = 320;
	if (glfwInit() != GL_TRUE) {
		printf("glfwInit() failed\n");
		return GL_FALSE;
	}

	if (glfwOpenWindow(width, height, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE) {
		printf("glfwOpenWindow() failed\n");
		return GL_FALSE;
	}

	return GL_TRUE;
}

void shutdown_gl(){
	glfwTerminate();
}

void on_surface_created() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
 
void on_surface_changed() {
    // No-op
}
 
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
}

