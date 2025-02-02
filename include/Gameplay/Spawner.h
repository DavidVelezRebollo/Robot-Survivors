#pragma once

#include <SFML/Graphics.hpp>
#include <Core/EnemyPool.h>

class Spawner {
	public:

		~Spawner() {
			m_enemyPool = nullptr;
			m_target = nullptr;
		}

		void initialize(sf::Vector2f position, Player* target, float timeToSpawn);
		void spawnEnemy();

		void update(float delta);
	protected:
		sf::Vector2f m_position{ 0.f, 0.f };
		EnemyPool* m_enemyPool{ nullptr };
		Player* m_target{ nullptr };

		float m_timeToSpawn{ 0.f };
		float m_spawnerDelta{ 0.f };
		float m_timeDelta{ 0.f };
};