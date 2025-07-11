#include <stdio.h>

#include "Application.h"
#include "core/EventManager.h"
#include "params.h"

namespace Core {
	Application::Application() : m_window(nullptr), m_renderer(nullptr), m_shouldQuit(true), m_activeScene(nullptr) {
		// m_shouldQuit at the start is true before successful initialization
		m_window = SDL_CreateWindow(Params::Window::title, Params::Window::width, Params::Window::height, SDL_WINDOW_HIDDEN);
		if (!m_window) {
			printf("Failed to init SDL_Window: %s\n", SDL_GetError());
			return;
		}

		m_renderer = new Renderer(m_window);

		// Init was a success
		SDL_ShowWindow(m_window);
		m_shouldQuit = false;
	}

	Application::~Application() {
		delete m_renderer;
		SDL_DestroyWindow(m_window);
	}

	void Application::Run() {
		while (!m_shouldQuit) {
			Core::EventManager::GetInstance().PollEvents();

			Update(0);
			m_activeScene->UpdateBase(0);

			m_renderer->RenderClear();
			m_renderer->Render(m_activeScene->GetGameObjects());
			m_renderer->RenderPresent();

			m_shouldQuit = Core::EventManager::GetInstance().ShouldQuit();
		}
	}

	void Application::SetActiveScene(Scene* scene) {
		m_activeScene = scene;
	}
}