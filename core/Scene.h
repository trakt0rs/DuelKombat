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
				obj->Update(deltaTime);
			}
		}

		void AddGameObject(GameObject* obj) {
			m_gameObjects.push_back(obj);
		}

		const std::vector<GameObject*>& GetGameObjects() const { return m_gameObjects; }
	private:
		std::vector<GameObject*> m_gameObjects;
	};
}