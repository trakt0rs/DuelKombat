#pragma once

#include <array>
#include <SDL3/SDL_events.h>

namespace Core {

	/// <summary>
	/// Singleton class responsible for handling input and SDL events.
	/// Tracks keyboard state across frames to detect key presses, releases, and holds.
	/// </summary>
	class EventManager {
	public:
		static EventManager& GetInstance() {
			if (instance == nullptr) {
				instance = new EventManager();
			}
			return *instance;
		}

		/// <summary>
		/// Polls SDL events and updates key state buffers.
		/// Should be called once per frame before processing events.
		/// </summary>
		void PollEvents();

		inline bool IsKeyPressed(SDL_Scancode key) const { return m_currentKeysPressed[key] && !m_previousKeysPressed[key]; }
		inline bool IsKeyReleased(SDL_Scancode key) const { return !m_currentKeysPressed[key] && m_previousKeysPressed[key]; }
		inline bool IsKeyHeld(SDL_Scancode key) const { return m_currentKeysPressed[key]; }
		inline bool ShouldQuit() const { return m_shouldQuit; }
		
	private:
		EventManager();
		~EventManager() = default;

		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;

		static EventManager* instance;

	private:
		std::array<bool, SDL_SCANCODE_COUNT> m_currentKeysPressed;
		std::array<bool, SDL_SCANCODE_COUNT> m_previousKeysPressed;

		bool m_shouldQuit;
	};
}