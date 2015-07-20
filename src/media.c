#include "media.h"
#include "math.h"
#include <SDL/SDL_mixer.h>

char display[64][32];
SDL_Rect pixel[64][32];
const int width = 640, height = 320, size=10;
int keystate_change;

byte last_pressed; int num_pressed;
const Uint8 *keystate = NULL;
static const SDL_Keycode keycodes[16] = {SDL_SCANCODE_X, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_Z, SDL_SCANCODE_C, SDL_SCANCODE_4, SDL_SCANCODE_R, SDL_SCANCODE_F, SDL_SCANCODE_V};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

Mix_Music *beep = NULL;

static inline void init_pixel(){
	for (int x = 0; x < 64; ++x){
		for (int y = 0; y < 32; ++y){
			pixel[x][y].x = x*size;
			pixel[x][y].y = y*size;
			pixel[x][y].w = size;
			pixel[x][y].h = size;

			display[x][y] = 0;
		}
	}
}

inline int init_media(){
	keystate = SDL_GetKeyboardState(&num_pressed);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0){  		
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) return 0;
		if ((beep = Mix_LoadMUS("beep.wav")) == NULL) return 0;
		if ((window = SDL_CreateWindow("Chip8js", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN)) == NULL) return 0;
		if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) return 0;

		init_pixel();
		return 1;
	}

	return 0;
}

inline void shutdown_media(){
	Mix_HaltMusic();
	Mix_FreeMusic(beep);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

 
inline void draw() {
	// simple draw update
	SDL_SetRenderDrawColor(renderer, 30,30,30,255);
	SDL_RenderClear(renderer);

	for (int x = 0; x < 64; ++x){
		for (int y = 0; y < 32; ++y){
			if (display[x][y]){
				SDL_SetRenderDrawColor(renderer, 240,240,240,255);
				SDL_RenderFillRect(renderer, &pixel[x][y]);
			}
		}
	}
	
}

inline void render_screen(){
	SDL_RenderPresent(renderer);
}


inline void poll_keyevent(){
	//SDL_PumpEvents();
	SDL_Event e;
	keystate_change = 0;
	while (SDL_PollEvent(&e)) {
		if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && !e.key.repeat){
			keystate_change = 1;
		}
	}
}

int key_pressed(byte k){
	//if (!keystate_change) return 0;

	if (k == ANY_KEY){
		if (num_pressed && keystate_change){
			keystate_change = 0;
			for (byte i = 0; i < 16; ++i){
				if (keystate[keycodes[i]]){
					last_pressed = i;
					return 1;
				}
			}
		}
		return 0;
	}else{
		return keystate[keycodes[k]];
	}
}

byte get_pressed(){
	return last_pressed;
}

void start_bell(){
	if(Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(beep, -1);
	}
}

void end_bell(){
	//SDL_PauseAudio(1);

	if(Mix_PlayingMusic() > 0) {
		Mix_HaltMusic();
	}

	
}