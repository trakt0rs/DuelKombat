#pragma once

#include <SDL3/SDL.h>

#include "Renderer.h"
#include "Scene.h"

namespace Core {

	/// <summary>
	/// The Application class is the core of the framework.
	/// It handles SDL window creation, initializes the renderer,
	/// runs the main application loop, calculates delta time,
	/// and manages active scenes.
	/// </summary>
	class Application {
	public:
		/// <summary>
		/// Initializes the SDL window and renderer.
		/// After setup, user-defined initialization can be performed.
		/// </summary>
		Application();
		~Application();

		/// <summary>
		/// Starts the main application loop.
		/// </summary>
		void Run();

	protected:
		/// <summary>
		/// Override this method to implement custom per-frame logic.
		/// Called once every frame with the elapsed time in seconds.
		/// </summary>
		virtual void Update(float deltaTime) = 0;

		/// <summary>
		/// Switches the active scene.
		/// Calls OnExit() on the current scene (if any),
		/// then OnEnter() on the new scene.
		/// </summary>
		/// <param name="scene">Pointer to the new scene to activate.</param>
		void SetActiveScene(Scene* scene);

	private:
		SDL_Window* m_window;
		Renderer* m_renderer;
		bool m_shouldQuit;

		Scene* m_activeScene;
	};

}
