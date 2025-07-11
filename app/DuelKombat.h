#pragma once

#include "core/Application.h"

namespace DK {
	class DuelKombat : public Core::Application {
	public:
		DuelKombat();
		~DuelKombat();

	protected:
		void Update(float deltaTime) override;
	};
}