#include <stdio.h>

#include "Application.h"
#include "EventManager.h"
#include "params.h"

namespace Core {
	Application::Application() : m_window(nullptr), m_renderer(nullptr), m_shouldQuit(true), m_activeScene(nullptr) {
		
		// Create SDL_Window, initially hidden
		m_window = SDL_CreateWindow(Params::Window::title, Params::Window::width, Params::Window::height, SDL_WINDOW_HIDDEN);
		if (!m_window) {
			printf("Failed to init SDL_Window: %s\n", SDL_GetError());
			return;
		}

		m_renderer = new Renderer(m_window);

		// Initialization successful - show the window and allow the main loop to start.
		SDL_ShowWindow(m_window);
		m_shouldQuit = false;
	}

	Application::~Application() {
		delete m_renderer;
		SDL_DestroyWindow(m_window);
	}

	void Application::Run() {
		uint64_t lastCounter = SDL_GetPerformanceCounter();
		const float targetFrameTime = 1.0f / Params::Window::targetFPS;

		while (!m_shouldQuit) {
			// Calculate elapsed time for this frame.
			uint64_t nowCounter = SDL_GetPerformanceCounter();
			float deltaTime = static_cast<float>(nowCounter - lastCounter) / static_cast<float>(SDL_GetPerformanceFrequency());
			lastCounter = nowCounter;

			Core::EventManager::GetInstance().PollEvents();

			Update(deltaTime);						// User defined per-frame logic.
			m_activeScene->UpdateBase(deltaTime);

			m_renderer->RenderClear();
			m_renderer->Render(m_activeScene->GetGameObjects());
			m_renderer->RenderPresent();

			// Maintain consisten frame rate by delaying if frame was proccessed too quickly
			float frameTime = static_cast<float>(SDL_GetPerformanceCounter() - nowCounter) / SDL_GetPerformanceFrequency();
			if (frameTime < targetFrameTime) {
				// convert seconds to nanoseconds
				float delayTime = (targetFrameTime - frameTime) * 1'000'000'000.0f;
				SDL_DelayPrecise(static_cast<uint32_t>(delayTime));
			}

			m_shouldQuit = Core::EventManager::GetInstance().ShouldQuit();
		}
	}

	void Application::SetActiveScene(Scene* scene) {
		if (m_activeScene) {
			m_activeScene->OnExit();
		}
		m_activeScene = scene;
		scene->OnEnter();
	}
}