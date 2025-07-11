#include "FightScene.h"

#include "Player.h"

namespace DK {
	FightScene::FightScene(){
		AddGameObject(new Player());
	}

	FightScene::~FightScene() {

	}
}