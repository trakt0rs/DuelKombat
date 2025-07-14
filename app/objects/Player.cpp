#include "Player.h"
#include <iostream>

#include "core/AssetManager.h"
#include "core/EventManager.h"

#include "app/components/PlayerController.h"

namespace DK {
	Player::Player() {
		transform = GetComponent<Core::Transform>();
		transform->scale = { 1.f, 1.f };
		Core::SpriteRenderer* spriteRenderer = AddComponent<Core::SpriteRenderer>(
			Core::AssetManager::GetInstance().GetTexture("smiley.jpg")
		);

		AddComponent<PlayerController>();
	}

	Player::~Player() {
	}
}