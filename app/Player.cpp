#include "Player.h"

#include <iostream>

namespace DK {
	Player::Player() {
		GetComponent<Core::Transform>()->scale = { 100, 100 };
		Core::ShapeRenderer* shapeRenderer = AddComponent<Core::ShapeRenderer>(SDL_Color{255 ,255, 255, 255});
	}

	Player::~Player() {

	}
}