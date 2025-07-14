#pragma once

#include <SDL3/SDL_pixels.h>

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "utils.h"
#include "Texture.h"

namespace Core {
	class GameObject;

	class Component {
	public:
		bool active = true;	// Component gets updated only if its active and its GameObject is active

		Component() = delete; // Prevent accidental usage
		Component(GameObject* parentObj) : parentObj(parentObj) {}
		virtual ~Component() = default;

		virtual void Update(float deltaTime) {}

	protected:
		GameObject* parentObj;
	};

	struct Transform : public Component {
		Vec2f position;
		Vec2f scale;
		float rotation;

		Transform(GameObject* parentObj, Vec2f position = { 0, 0 }, Vec2f scale = { 1, 1 }, float rotation = 0.0f) : Component(parentObj), position(position), scale(scale), rotation(rotation) {}
	};

	// TODO: Future - SpriteRenderer should have z-index
	struct SpriteRenderer : public Component {
		SDL_Color color;
		Texture* texture;

		SpriteRenderer(GameObject* parentObj, Texture* texture = nullptr, SDL_Color color = { 255, 255, 255, 255 }) : Component(parentObj), color(color), texture(texture) {}
	};
	
	class GameObject {
	public:
		bool active = true;	// GameObject gets updated only if its active

		GameObject() {
			AddComponent<Transform>(); // GameObject on default has Transform component
		};
		virtual ~GameObject() = default;

		void UpdateBase(float deltaTime) {
			for (auto& [type, component] : m_components) {
				if(component->active)
					component->Update(deltaTime);
			}
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			std::type_index type = typeid(T);
			if (m_components.contains(type)) return nullptr;

			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* raw = static_cast<T*>(component.get());
			m_components[type] = std::move(component);

			return raw;
		}

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