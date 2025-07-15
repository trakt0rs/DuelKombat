#include "PlayerController.h"

#include "core/EventManager.h"

#include <iostream>

namespace DK {

	PlayerController::PlayerController(Core::GameObject* parentObj) : Core::Component(parentObj) {
		m_transform = parentObj->GetComponent<Core::Transform>();
	}

	void PlayerController::Update(float deltaTime) {
		float direction = static_cast<float>(Core::EventManager::GetInstance().IsKeyHeld(SDL_SCANCODE_D)) - static_cast<float>(Core::EventManager::GetInstance().IsKeyHeld(SDL_SCANCODE_A));

		m_transform->position.x += direction * deltaTime * 100;

		if (m_transform->position.x > 600.0f) {
			parentObj->Destroy();
		}
	}
}