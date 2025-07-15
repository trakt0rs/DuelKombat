#include "Scene.h"

namespace Core {
	void Scene::UpdateBase(float deltaTime) {
		Update(deltaTime);

		// Update GameObjects in scene
		for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();) {
			if ((*it)->ShouldDestroy()) {
				it = m_gameObjects.erase(it);
				continue;
			}
			if ((*it)->active) {
				(*it)->UpdateBase(deltaTime);
			}
			it++;
		}
	}

	const std::vector<std::unique_ptr<GameObject>>& Scene::GetGameObjects() const {
		return m_gameObjects;
	}

	void Scene::AddGameObject(std::unique_ptr<GameObject> obj) {
		m_gameObjects.push_back(std::move(obj));
	}
}