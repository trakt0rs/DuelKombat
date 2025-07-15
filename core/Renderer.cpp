#include "Renderer.h"

#include <iostream>
#include <memory>

#include "AssetManager.h"

namespace Core {
	Renderer::Renderer(SDL_Window* window) {
		m_renderer = SDL_CreateRenderer(window, NULL);
		if (!m_renderer) {
			std::cout << SDL_GetError() << std::endl;
		}

		AssetManager::GetInstance().Init(m_renderer);
	}

	Renderer::~Renderer() {
		SDL_DestroyRenderer(m_renderer);
	}

	void Renderer::RenderClear() {
		// Clear screen with black color
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::Render(const std::vector<std::unique_ptr<GameObject>>& gameObjects) const {
		for (const auto& gameObject : gameObjects) {
			if (!gameObject->active) continue;	// Skip inactive gameobjects

			SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
			if (spriteRenderer != nullptr) {	// Skip if no SpriteRenderer

				if (!spriteRenderer->active) continue;	// Skip inactive SpriteRenderers

				// Get the destination rectangle based on position, scale, and texture size
				Transform* transform = gameObject->GetComponent<Transform>();
				SDL_FRect destinationRect = {
					transform->position.x,
					transform->position.y,
					transform->scale.x * spriteRenderer->texture->textureSize.x,
					transform->scale.y * spriteRenderer->texture->textureSize.y
				};

				// Apply color and alpha modulations to texture
				SDL_SetTextureColorMod(spriteRenderer->texture->texture, spriteRenderer->color.r, spriteRenderer->color.g, spriteRenderer->color.b);
				SDL_SetTextureAlphaMod(spriteRenderer->texture->texture, spriteRenderer->color.a);

				// TODO: Rotate sprite based on a pivot

				// Finally render texture
				SDL_RenderTexture(m_renderer, spriteRenderer->texture->texture, nullptr, &destinationRect);
			}
		}
	}

	void Renderer::RenderPresent() {
		SDL_RenderPresent(m_renderer);
	}
}