#pragma once

#include <Core/SoundManager.h>
#include <Core/GameManager.h>
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Gameplay/Player.h>


class Enemy : public GameObject
{
	public:
		~Enemy() override {
			m_target = nullptr;
		}

		bool init(sf::Vector2f position, sf::Texture* enemyTexture, Player* target);

		bool isDead();
		void resetEnemy(sf::Vector2f position);
		void takeDamage(float amount);
		float getDamage() const { return m_damage; }

		void onCollision(GameObject* collision) override;
		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

	protected:
		virtual void enemyBehaviour(float delta) = 0;
		virtual void initStats() = 0;

		void die();

		Player* m_target{ nullptr };

		float m_damage{ 0.f };
		float m_maxHp{ 1.f };
		float m_currentHp{ 1.f };
		float m_speed{ 150.f };
		float m_experience{ 0.f };
		
		float m_damageThreshold{ 200.f };
		float m_deltaThreshold{ 0.f };
};