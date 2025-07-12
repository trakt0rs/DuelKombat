#pragma once

#include <SDL3/SDL_pixels.h>

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "utils.h"
#include "Texture.h"

namespace Core {
	class Component {
	public:
		bool active = true;	// Component gets updated only if its active and its GameObject is active

		Component() = default;
		virtual ~Component() = default;

		virtual void Update(float deltaTime) {}
	};

	struct Transform : public Component {
		Vec2f position;
		Vec2f scale;
		float rotation;

		Transform(Vec2f position = { 0, 0 }, Vec2f scale = { 1, 1 }, float rotation = 0.0f) : position(position), scale(scale), rotation(rotation) {}
	};

	// TODO: Future - SpriteRenderer should have z-index
	struct SpriteRenderer : public Component {
		SDL_Color color;
		Texture* texture;

		SpriteRenderer(Texture* texture = nullptr, SDL_Color color = { 255, 255, 255, 255 }) : color(color), texture(texture) {}
	};
	
	class GameObject {
	public:
		bool active = true;	// GameObject gets updated only if its active

		GameObject() {
			AddComponent<Transform>(); // GameObject on default has Transform component
		};
		virtual ~GameObject() = default;

		// TODO: Should GameObject have central client side Update if it has a component system?
		virtual void Update(float deltaTime) {};
		void UpdateBase(float deltaTime) {
			Update(deltaTime);
			for (auto& [type, component] : m_components) {
				if(component->active)
					component->Update(deltaTime);
			}
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			std::type_index type = typeid(T);
			if (m_components.contains(type)) return nullptr;

			m_components[type] = std::make_unique<T>(std::forward<Args>(args)...);
			return static_cast<T*>(m_components[type].get());
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