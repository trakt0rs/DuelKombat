#include "EventManager.h"

namespace Core {

	EventManager* EventManager::instance = nullptr;


	EventManager::EventManager() : m_previousKeysPressed(), m_currentKeysPressed(), m_shouldQuit(false) {}

	void EventManager::PollEvents() {

		// Reset keys
		m_previousKeysPressed = m_currentKeysPressed;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				m_shouldQuit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (!event.key.repeat)
					m_currentKeysPressed[event.key.scancode] = true;
				break;
			case SDL_EVENT_KEY_UP:
				m_currentKeysPressed[event.key.scancode] = false;
				break;
			}
		}
	}

}