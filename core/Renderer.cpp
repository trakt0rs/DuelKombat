#include "Renderer.h"

#include <iostream>

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
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::Render(const std::vector<GameObject*>& gameObjects) const {
		for (const auto& gameObject : gameObjects) {
			if (!gameObject->active) continue;
			SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

			if (spriteRenderer != nullptr) {
				if (!spriteRenderer->active) continue;
				Transform* transform = gameObject->GetComponent<Transform>();
				SDL_FRect dstRect = {
					transform->position.x,
					transform->position.y,
					transform->scale.x * spriteRenderer->texture->textureSize.x,
					transform->scale.y * spriteRenderer->texture->textureSize.y
				};

				SDL_SetTextureColorMod(spriteRenderer->texture->texture, spriteRenderer->color.r, spriteRenderer->color.g, spriteRenderer->color.b);
				SDL_SetTextureAlphaMod(spriteRenderer->texture->texture, spriteRenderer->color.a);

				// TODO: Rotate sprite based on a pivot

				SDL_RenderTexture(m_renderer, spriteRenderer->texture->texture, nullptr, &dstRect);
			}
		}
	}

	void Renderer::RenderPresent() {
		SDL_RenderPresent(m_renderer);
	}
}