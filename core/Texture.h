#pragma once

#include <SDL3/SDL.h>
#include "utils.h"

namespace Core {
	struct Texture {
		SDL_Texture* texture;
		Vec2i textureSize;

		Texture(SDL_Texture* texture, Vec2i textureSize) : texture(texture), textureSize(textureSize) {}
		~Texture() { SDL_DestroyTexture(texture); }
	};
}