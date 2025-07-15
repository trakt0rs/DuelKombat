#pragma once

#include <SDL3/SDL_pixels.h>

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "utils.h"
#include "Texture.h"

namespace Core {
	class GameObject;

	/// <summary>
	/// Base for all components.
	/// Components attach to GameObjects and provide modular functionality.
	/// Only active components on active GameObjects will be updated.
	/// </summary>
	class Component {
	public:
		bool active = true;

		Component() = delete; // Prevent usage without a parent GameObject
		explicit Component(GameObject* parentObj);
		virtual ~Component() = default;

		/// <summary>
		/// Override to define per-frame logic for component
		/// Called only if both the component and its GameObject are active
		/// </summary>
		virtual void Update(float deltaTime) {}

	protected:
		GameObject* parentObj;
	};

	/// <summary>
	/// Component for position, scale, and rotation.
	/// Acts as the transform of a GameObject in 2D space.
	/// </summary>
	struct Transform : public Component {
		Vec2f position;
		Vec2f scale;
		float rotation;

		Transform(GameObject* parentObj, Vec2f position = { 0, 0 }, Vec2f scale = { 1, 1 }, float rotation = 0.0f);
	};

	/// <summary>
	/// Component responsible for rendering a texture.
	/// Includes a color tint and optional transparency
	/// </summary>
	struct SpriteRenderer : public Component {
		SDL_Color color;
		Texture* texture;

		SpriteRenderer(GameObject* parentObj, Texture* texture = nullptr, SDL_Color color = { 255, 255, 255, 255 });
	};
	
	/// <summary>
	/// GameObject represents an entity in the scene.
	/// It can have multiple unique components and be toggled active/inactive.
	/// By default, every GameObject is created with a Transform component.
	/// </summary>
	class GameObject {
	public:
		bool active = true;	// GameObject gets updated only if its active
		bool destroyFlag = false;

		GameObject();
		virtual ~GameObject() = default;

		/// <summary>
		/// Updates all attached components that are active.
		/// Should be called each frame.
		/// </summary>
		/// <param name="deltaTime"></param>
		void UpdateBase(float deltaTime);

		/// <summary>
		/// Marks a GameObject for a destruction
		/// </summary>
		void Destroy() { destroyFlag = true; }

		/// <returns>Returns true if the GameObject is marked for destruction</returns>
		bool ShouldDestroy() { return destroyFlag; }

		/// <summary>
		/// Adds a compnent of type T to this GameObject
		/// </summary>
		/// <returns>Returns added component or nullptr if adding component failed</returns>
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			std::type_index type = typeid(T);
			if (m_components.contains(type)) return nullptr;

			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* raw = static_cast<T*>(component.get());
			m_components[type] = std::move(component);

			return raw;
		}

		/// <returns>Retrieves a component from GameObject if it exists with type T or nullptr if compnent doesnt exist</returns>
		template<typename T>
		T* GetComponent() {
			auto it = m_components.find(typeid(T));
			if (it == m_components.end()) {
				return nullptr;
			}
			return static_cast<T*>(it->second.get());
		}
	
	private:
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	};
}