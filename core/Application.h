#pragma once

#include <SDL3/SDL.h>

#include "Renderer.h"
#include "Scene.h"

namespace Core {

	class Application {
	public:
		Application();
		~Application();

		void Run();

	protected:
		virtual void Update(float deltaTime) = 0;
		
		void SetActiveScene(Scene* scene);

	private:
		SDL_Window* m_window;
		Renderer* m_renderer;
		bool m_shouldQuit;

		Scene* m_activeScene;
	};

}