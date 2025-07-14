#include "EventManager.h"

namespace Core {

	EventManager* EventManager::instance = nullptr;


	EventManager::EventManager() : lastKeysPressed(), keysPressed(), shouldQuit(false) {}

	void EventManager::PollEvents() {

		// Reset keys
		lastKeysPressed = keysPressed;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				shouldQuit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (!event.key.repeat)
					keysPressed[event.key.scancode] = true;
				break;
			case SDL_EVENT_KEY_UP:
				keysPressed[event.key.scancode] = false;
				break;
			}
		}
	}

}