#pragma once

#include <Gameplay/GameObject.h>
#include <Core/SoundManager.h>

class Player : public GameObject
{
	public:

		~Player() override = default;
		void init(float delta);

		void addExp(float amount);

		void onCollision(GameObject* collision) override;
		void update(float delta) override;
		void render(sf::RenderWindow& window) override;

	protected:
		void calculateDirection();
		void calculateLookDirection();
		void levelUp();
		void takeDamage(float amount);
		void die();

		bool m_isDead{ false };

		float m_maxHp{ 100.f };
		float m_currentHp{ 0.f };
		float m_damageThreshold{ 500.f };
		float m_deltaThreshold{ 0.f };

		sf::Vector2f m_direction;
		sf::Vector2f m_speed = { 400.f, 400.f };
		float shootCooldown = 100.f;

		float m_currentExp{ 0 };
		float m_neededExp{ 100.f };
		int m_level{ 1 };
		const float m_growthFactor{ 1.1f };
};