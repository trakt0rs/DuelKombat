#include "AssetManager.h"

#include <stdio.h>
#include <SDL3_image/SDL_image.h>

namespace Core {
	AssetManager* AssetManager::instance = nullptr;

	void AssetManager::Init(SDL_Renderer* renderer) {
		m_renderer = renderer;
	}

	Texture* AssetManager::GetTexture(const std::string& path) {
		const std::string key = "assets\\" + path;

		// Check if already loaded
		auto it = m_textures.find(key);
		if (it != m_textures.end()) {
			return it->second.get();
		}

		// Load Texture
		SDL_Surface* surface = IMG_Load(key.c_str());
		if (!surface) {
			printf("Failed to load surface for texture: %s\n", SDL_GetError());
			return nullptr;
		}

		SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (!sdl_texture) {
			printf("Failed to create texture from surface: %s\n", SDL_GetError());
			return nullptr;
		}

		auto texture = std::make_unique<Texture>(sdl_texture, Vec2i{ surface->w, surface->h });
		SDL_DestroySurface(surface);

		m_textures[key] = std::move(texture);
		return m_textures[key].get();
	}
}