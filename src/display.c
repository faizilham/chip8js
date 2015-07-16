#include "display.h"

char display[64][32];
SDL_Rect pixel[64][32];
const int width = 640, height = 320, size=10;
SDL_Surface *screen = NULL;

static inline void init_pixel(){
	for (int x = 0; x < 64; ++x){
		for (int y = 0; y < 32; ++y){
			pixel[x][y].x = x*size;
			pixel[x][y].y = y*size;
			pixel[x][y].w = size;
			pixel[x][y].h = size;

			display[x][y] = (x % 2 == y % 2);
		}
	}
}

inline int init_display(){
	if (SDL_Init(SDL_INIT_VIDEO) == 0){
		if ((screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))!=NULL){
			init_pixel();
			return 1;
		}
	}

	return 0;
}

inline void shutdown_display(){
	SDL_FreeSurface(screen);
	SDL_Quit();
}

 
inline void draw() {
	// simple draw update
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	for (int x = 0; x < 64; ++x){
		for (int y = 0; y < 32; ++y){
			if (display[x][y]){
				SDL_FillRect(screen, &pixel[x][y], SDL_MapRGB(screen->format, 255, 255, 255));
			}
		}
	}
	SDL_Flip(screen);
}

