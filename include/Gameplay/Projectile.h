#pragma once

#include <Gameplay/GameObject.h>

class Projectile : public GameObject
{
	public:
		~Projectile() = default;

		void init(const sf::Texture* texture, sf::Vector2f playerPos, sf::Vector2f direction, float damage, bool canHurtPlayer, bool canPierce = false);

		float getDamage() const { return m_damage; }
		void setPierce(bool pierce) { m_pierce = pierce; }
		bool pierce() const { return m_pierce; }
		void updateTexture(sf::Texture* texture) {
			if (m_sprite.getTexture() == texture) return;

			m_sprite.setTexture(*texture);
		}
		void setCanHurtPlayer(bool canHurt) { m_canHurtPlayer = canHurt; }
		bool canHurtPlayer() const { return m_canHurtPlayer; }

		void onCollision(GameObject* collision) override;
		void update(float delta) override;
		void render(sf::RenderWindow& window) override;

		void activate() override;
		void deactivate() override;

		bool isOutOfBounds() const;
		void setDirection(sf::Vector2f direction);
	protected:

		sf::Vector2f m_direction;
		sf::Vector2u m_renderWindowSize;
		sf::Vector2f m_playerPos;

		float scale{ 1.f };
		float m_speed{ 2.f };
		float m_damage{ 0.f };
		bool m_pierce{ false };
		bool m_canHurtPlayer{ false };
};