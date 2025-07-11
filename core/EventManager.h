#pragma once

#include <array>
#include <SDL3/SDL_events.h>

namespace Core {

	class EventManager {
	public:
		static EventManager& GetInstance() {
			if (instance == nullptr) {
				instance = new EventManager();
			}
			return *instance;
		}

		void PollEvents();

		inline bool IsKeyPressed(SDL_Scancode key) const { return keysPressed[key] && !lastKeysPressed[key]; }
		inline bool IsKeyReleased(SDL_Scancode key) const { return !keysPressed[key] && lastKeysPressed[key]; }
		inline bool IsKeyHeld(SDL_Scancode key) const { return keysPressed[key]; }
		inline bool ShouldQuit() const { return shouldQuit; }
		
	private:
		EventManager();
		~EventManager() = default;

		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;

		static EventManager* instance;

	private:
		// For capturing all keys 
		std::array<bool, SDL_SCANCODE_COUNT> keysPressed;
		std::array<bool, SDL_SCANCODE_COUNT> lastKeysPressed;

		bool shouldQuit;
	};

}