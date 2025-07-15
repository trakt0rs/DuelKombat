#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "GameObject.h"

namespace Core {

	/// <summary>
	/// The Renderer class encapsulates SDL rendering functionallity.
	/// It provides methods to clear the screen, render game objects, and present the final frame
	/// </summary>
	class Renderer {
	public:
		/// <summary>
		/// Initializes the SDL rendering using the window provided
		/// </summary>
		/// <param name="window">Pointer to the SDL window for rendering</param>
		Renderer(SDL_Window* window);
		~Renderer();

		/// <summary>
		/// Clears the screen with the current clear color
		/// Should be called at the start of each frame
		/// </summary>
		void RenderClear();

		/// <summary>
		/// Renders all provided game objects that have a SpriteRenderer component.
		/// Skips objects without SpriteRenderer and if SpriteRenderer is deactivated or GameObject is deactivated
		/// </summary>
		/// <param name="gameObjects">List of all game objects in the scene</param>
		void Render(const std::vector<std::unique_ptr<GameObject>>& gameObjects) const;

		/// <summary>
		/// Presents the rendered frame of the window.
		/// Should be called at the end of each frame.
		/// </summary>
		void RenderPresent();

	private:
		SDL_Renderer* m_renderer;
	};

}