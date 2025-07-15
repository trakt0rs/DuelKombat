#include "FightScene.h"

#include "app/objects/Player.h"

#include <memory>
#include <stdio.h>

namespace DK {
	FightScene::FightScene(){
		AddGameObject(std::make_unique<Player>());
	}

	FightScene::~FightScene() {

	}

	void FightScene::OnEnter() {
		printf("Entered scene...\n");
	}
}