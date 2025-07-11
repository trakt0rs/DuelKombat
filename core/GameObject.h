#pragma once

#include <SDL3/SDL.h>
#include "utils.h"

namespace Core {
	class GameObject {
	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		virtual void Update(float deltaTime) = 0;
	
	protected:
		Vec2f position;
	};
}