#pragma once

#include <SDL3/SDL.h>

namespace Core {

	class Application {
	public:
		Application();
		~Application();

		void Run();

	protected:
		virtual void Update(float deltaTime) = 0;

	private:
		void M_Render();

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		bool m_shouldQuit;
	};

}