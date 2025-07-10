#include <stdio.h>

#include "Application.h"
#include "core/EventManager.h"
#include "params.h"

namespace DK {
	Application::Application() : m_window(nullptr), m_renderer(nullptr), m_shouldQuit(true) {
		// m_shouldQuit at the start is true before successful initialization
		m_window = SDL_CreateWindow(Params::Window::title, Params::Window::width, Params::Window::height, SDL_WINDOW_HIDDEN);
		if (!m_window) {
			printf("Failed to init SDL_Window: %s\n", SDL_GetError());
			return;
		}

		m_renderer = SDL_CreateRenderer(m_window, NULL);
		if (!m_renderer) {
			printf("Failed to create SDL_Renderer: %s\n", SDL_GetError());
			return;
		}

		// Init was a success
		SDL_ShowWindow(m_window);
		m_shouldQuit = false;
	}

	Application::~Application() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	void Application::Run() {
		while (!m_shouldQuit) {
			Core::EventManager::GetInstance().PollEvents();

			m_shouldQuit = Core::EventManager::GetInstance().ShouldQuit();
		}
	}

	void Application::M_Update(float deltaTime) {

	}

	void Application::M_Render() {
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);



		SDL_RenderPresent(m_renderer);
	}
}