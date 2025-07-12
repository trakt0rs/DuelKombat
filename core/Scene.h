#pragma once

#include "GameObject.h"

namespace Core {
	class Scene {
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Update(float deltaTime) {};
		void UpdateBase(float deltaTime) {
			Update(deltaTime);
			for (GameObject* obj : m_gameObjects) {
				if(obj->active)
					obj->Update(deltaTime);
			}
		}

		void AddGameObject(GameObject* obj) {
			m_gameObjects.push_back(obj);
		}
		// TODO: Scene should have OnExit() OnEnter()

		const std::vector<GameObject*>& GetGameObjects() const { return m_gameObjects; }
	private:
		// TODO: Should not contain raw pointers, Future - replaced by GameObjectManager
		std::vector<GameObject*> m_gameObjects;
	};
}