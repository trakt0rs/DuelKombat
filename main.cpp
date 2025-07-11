#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "app/DuelKombat.h"

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	if (!TTF_Init()) {
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	DK::DuelKombat duelKombat;
	duelKombat.Run();

	SDL_Quit();
	TTF_Quit();
	return 0;
}