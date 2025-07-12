#include "Player.h"
#include <iostream>

#include "core/AssetManager.h"

namespace DK {
	Player::Player() {
		GetComponent<Core::Transform>()->scale = { 1.f, 1.f };
		Core::SpriteRenderer* spriteRenderer = AddComponent<Core::SpriteRenderer>(
			Core::AssetManager::GetInstance().GetTexture("smiley.jpg")
		);
	}

	Player::~Player() {

	}
}