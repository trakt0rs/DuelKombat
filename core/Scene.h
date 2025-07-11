#pragma once

#include <SDL3/SDL.h>

namespace Core {
	class Scene {
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Update(float deltaTime) = 0;
	};
}