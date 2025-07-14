#include "DuelKombat.h"

#include <iostream>

namespace DK {
	DuelKombat::DuelKombat() {
		SetActiveScene(&fightScene);
	}

	DuelKombat::~DuelKombat() {

	}

	void DuelKombat::Update(float deltaTime) {
		std::cout << 1.0f / deltaTime << std::endl;
	}
}