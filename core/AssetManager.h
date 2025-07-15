#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

#include "Texture.h"

namespace Core {

	/// <summary>
	/// Singleton class responsible for managing and caching texture assets.
	/// Prevents reloading the same texture mulitple times by storing them in memory
	/// </summary>
	class AssetManager {
	public:
		static AssetManager& GetInstance() {
			if (instance == nullptr) {
				instance = new AssetManager();
			}
			return *instance;
		}

		/// <summary>
		/// Initializes the asset manager with the SDL renderer.
		/// This must be called before loading any textures.
		/// </summary>
		/// <param name="renderer">Pointer to the SDL_Renderer used for texture creation.</param>
		void Init(SDL_Renderer* renderer);

		/// <summary>
		/// Loads and returns a texture from the specific file path.
		/// If the texture was already loaded, the cached instance is returned.
		/// </summary>
		/// <param name="path">Path to the texture file starting with "assets/".</param>
		/// <returns>Pointer to the loaded Texture.</returns>
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