#include "FightScene.h"

#include "app/objects/Player.h"

namespace DK {
	FightScene::FightScene(){
		AddGameObject(new Player());
	}

	FightScene::~FightScene() {

	}
}