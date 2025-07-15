#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

namespace Core {
	class Scene {
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Update(float deltaTime) {};
		virtual void OnEnter() {};
		virtual void OnExit() {};

		void UpdateBase(float deltaTime);

		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;
		void AddGameObject(std::unique_ptr<GameObject> obj);

	public:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	};
}