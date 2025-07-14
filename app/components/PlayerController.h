#pragma once

#include "core/GameObject.h"

namespace DK {
	class PlayerController : public Core::Component {
	public:
		PlayerController(Core::GameObject* parentObj);

		void Update(float deltaTime) override;

	private:
		Core::Transform* m_transform;
	};
}