#include "Renderer.h"

#include <iostream>

namespace Core {
	Renderer::Renderer(SDL_Window* window) {
		m_renderer = SDL_CreateRenderer(window, NULL);
		if (!m_renderer) {
			std::cout << SDL_GetError() << std::endl;
		}
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
			ShapeRenderer* shapeRenderer = gameObject->GetComponent<ShapeRenderer>();
			if (shapeRenderer != nullptr) {
				Transform* transform = gameObject->GetComponent<Transform>();
				SDL_FRect dstRect = {
					transform->position.x,
					transform->position.y,
					transform->scale.x,
					transform->scale.y
				};
				SDL_SetRenderDrawColor(m_renderer, shapeRenderer->color.r, shapeRenderer->color.g, shapeRenderer->color.b, shapeRenderer->color.a);
				SDL_RenderFillRect(m_renderer, &dstRect);
			}
		}
	}

	void Renderer::RenderPresent() {
		SDL_RenderPresent(m_renderer);
	}
}