#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace sf
{
	class RenderWindow;
}

class GameObject
{
	public:

		GameObject() = default;
		GameObject(float x, float y) : m_position{ x,y } {}
		virtual ~GameObject() = default;

		const sf::Vector2f& getPosition() const { return m_position; }
		sf::Vector2f& getPosition() { return m_position; }
		void setPosition(const sf::Vector2f& newPosition) { 
			m_position = newPosition;
			m_sprite.setPosition(newPosition);
		}

		sf::FloatRect getBounds() { return m_sprite.getGlobalBounds(); }

		virtual void activate() { m_isActive = true; }
		virtual void deactivate() { m_isActive = false; }
		bool isActive() const { return m_isActive; }

		virtual void onCollision(GameObject* collision) = 0;
		virtual void update(float delta) = 0;
		virtual void render(sf::RenderWindow& window) = 0;

	protected:
		sf::Sprite m_sprite;
		sf::Vector2f m_position{ .0f, .0f };
		bool m_isActive{ false };
};