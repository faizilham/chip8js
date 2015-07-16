#include "display.h"

char display[64][32];
SDL_Rect pixel[64][32];
const int width = 640, height = 320, size=10;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

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
		if ((window = SDL_CreateWindow("Chip8js", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN)) == NULL) return 0;
		if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) return 0;

		//if ((screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))!=NULL){
			init_pixel();
			return 1;
		//}
	}

	return 0;
}

inline void shutdown_display(){
	//SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

 
inline void draw() {
	// simple draw update
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);

	for (int x = 0; x < 64; ++x){
		for (int y = 0; y < 32; ++y){
			if (display[x][y]){
				SDL_SetRenderDrawColor(renderer, 255,255,255,255);
				SDL_RenderFillRect(renderer, &pixel[x][y]);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

