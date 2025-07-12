#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Texture.h"

namespace Core {
	class AssetManager {
	public:
		static AssetManager& GetInstance() {
			if (instance == nullptr) {
				instance = new AssetManager();
			}
			return *instance;
		}

		void Init(SDL_Renderer* renderer);

		Texture* GetTexture(const std::string& path);

	private:
		AssetManager() = default;
		~AssetManager() = default;

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		static AssetManager* instance;

	private:
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
		SDL_Renderer* m_renderer = nullptr;
	};
}