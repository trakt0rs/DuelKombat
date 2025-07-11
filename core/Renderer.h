#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "GameObject.h"

namespace Core {
	class Renderer {
	public:
		Renderer(SDL_Window* window);
		~Renderer();

		void RenderClear();
		void Render(const std::vector<GameObject*>& gameObjects) const;
		void RenderPresent();

	private:
		SDL_Renderer* m_renderer;
	};
}