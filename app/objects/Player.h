#pragma once

#include "core/GameObject.h"

namespace DK {
	class Player : public Core::GameObject {
	public:
		Player();
		~Player();

	private:
		Core::Transform* transform;
	};
}