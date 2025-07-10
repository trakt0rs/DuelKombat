#pragma once

#include <SDL3/SDL.h>

namespace DK {

	class Application {
	public:
		Application();
		~Application();

		void Run();

	private:
		void M_Update(float deltaTime);
		void M_Render();

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		bool m_shouldQuit;
	};

}