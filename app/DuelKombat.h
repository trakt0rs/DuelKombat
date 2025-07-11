#pragma once

#include "core/Application.h"

#include "FightScene.h"

namespace DK {
	class DuelKombat : public Core::Application {
	public:
		DuelKombat();
		~DuelKombat();

	private:
		void Update(float deltaTime) override;

	private:
		FightScene fightScene;
	};
}