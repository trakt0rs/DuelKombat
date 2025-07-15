#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

namespace Core {

	/// <summary>
	/// Represents a scene in the application, containing nad managing GameObjects.
	/// Supports lifecycle hooks for entering and exiting the scene.
	/// </summary>
	class Scene {
	public:
		Scene() = default;
		virtual ~Scene() = default;

		/// <summary>
		/// Called every frame. Override to implement custom scene update logic.
		/// </summary>
		virtual void Update(float deltaTime) {};

		/// <summary>
		/// Called when the scene becomes the active scene.
		/// Override to implement custum initialization or setup.
		/// </summary>
		virtual void OnEnter() {};

		/// <summary>
		/// Called when the scene is being swapped out.
		/// Override to handle cleanup or state saving.
		/// </summary>
		virtual void OnExit() {};

		/// <summary>
		/// Updates all GameObjects in the scene. Should be called each frame.
		/// </summary>
		void UpdateBase(float deltaTime);

		/// <summary>
		/// Returns const reference to all GameObjects in the scene.
		/// Used by Renderer
		/// </summary>
		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

		/// <summary>
		/// Adds new GameObject to the scene.
		/// </summary>
		/// <param name="obj">Unique pointer to GameObject to add.</param>
		void AddGameObject(std::unique_ptr<GameObject> obj);

	private:
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
	};

}