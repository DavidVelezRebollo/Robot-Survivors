#pragma once

#include "Gameplay/Projectile.h"

class BulletPool
{
	public:
		static BulletPool* getInstance() {
			if (m_instance != nullptr) return m_instance;

			m_instance = new BulletPool;
			return m_instance;
		}

		~BulletPool() {
			for (Projectile* bullet : m_bullets) {
				delete bullet;
				bullet = nullptr;
			}

			m_bullets.clear();
			m_instance = nullptr;
		}

		Projectile* getBullet(char* texture, sf::Vector2f position, sf::Vector2f direction, float damage, bool canHurtPlayer, bool canPierce = false);

		void update(float delta);
		void render(sf::RenderWindow& window);
	private:
		static BulletPool* m_instance;
		std::vector<Projectile*> m_bullets;
};