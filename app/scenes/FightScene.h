#pragma once

#include "core/Scene.h"

namespace DK {
	class FightScene : public Core::Scene {
	public:
		FightScene();
		~FightScene();

		void OnEnter() override;
	};
}