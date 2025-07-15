#include "GameObject.h"

namespace Core {

	Component::Component(GameObject* parentObj) : parentObj(parentObj) {}

	Transform::Transform(GameObject* parentObj, Vec2f position, Vec2f scale, float rotation)
		: Component(parentObj), position(position), scale(scale), rotation(rotation) {}

	SpriteRenderer::SpriteRenderer(GameObject* parentObj, Texture* texture, SDL_Color color)
		: Component(parentObj), color(color), texture(texture) {}

	GameObject::GameObject() {
		AddComponent<Transform>(); // GameObject on default has Transform component
	};

	void GameObject::UpdateBase(float deltaTime) {
		for (auto& [type, component] : m_components) {
			if (component->active)
				component->Update(deltaTime);
		}
	}
}