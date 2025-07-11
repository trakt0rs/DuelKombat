#pragma once

#include <SDL3/SDL_pixels.h>

#include <unordered_map>
#include <typeindex>
#include <memory>

#include "utils.h"

namespace Core {
	struct Component {
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

	struct ShapeRenderer : public Component {
		SDL_Color color;

		ShapeRenderer(SDL_Color color = { 255, 255, 255, 255 }) : color(color) {}
	};
	
	class GameObject {
	public:
		// GameObject on default has Transform component
		GameObject() {
			AddComponent<Transform>();
		};
		virtual ~GameObject() = default;

		virtual void Update(float deltaTime) {};
		void UpdateBase(float deltaTime) {
			Update(deltaTime);
			for (auto& [type, component] : m_components) {
				component->Update(deltaTime);
			}
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args) {
			std::type_index type = typeid(T);
			if (m_components.contains(type)) return nullptr;

			m_components[type] = std::make_shared<T>(std::forward<Args>(args)...);
			return std::static_pointer_cast<T>(m_components[type]).get();
		}

		template<typename T>
		T* GetComponent() {
			auto it = m_components.find(typeid(T));
			if (it == m_components.end()) {
				return nullptr;
			}
			return std::static_pointer_cast<T>(it->second).get();
		}
	
	private:
		std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	};
}