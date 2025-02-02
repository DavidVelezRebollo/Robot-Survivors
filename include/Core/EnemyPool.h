#pragma once

#include "Gameplay/Enemy.h"
#include "Gameplay/Shooter.h"

class EnemyPool {
	public:
		~EnemyPool() {
			for (Enemy* enemy : m_enemies) {
				delete enemy;
				enemy = nullptr;
			}

			m_activeEnemies.clear();
			m_enemies.clear();
			s_instance = nullptr;
		}

		static EnemyPool* getInstance() {
			if (s_instance == nullptr) {
				s_instance = new EnemyPool();
			}

			return s_instance;
		}

		Enemy* getEnemy(sf::Vector2f position, Player* target);
		void unloadEnemies();

		void update(float delta);
		void render(sf::RenderWindow& window);
	private:
		static EnemyPool* s_instance;

		Enemy* parseEnemy(int num);
		sf::Texture* parseTexture(int num);

		std::vector<Enemy*> m_enemies;
		std::vector<Enemy*> m_activeEnemies;
};