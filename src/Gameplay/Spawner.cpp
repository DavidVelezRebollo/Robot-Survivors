#include "Gameplay/Spawner.h"
#include <iostream>

void Spawner::initialize(sf::Vector2f position, Player* target, float timeToSpawn)
{
	m_position = position;
	m_enemyPool = EnemyPool::getInstance();
	m_target = target;
	m_timeToSpawn = timeToSpawn;

	m_spawnerDelta = timeToSpawn;
}

void Spawner::spawnEnemy()
{
	m_enemyPool->getEnemy(m_position, m_target);
}

void Spawner::update(float delta)
{
	m_spawnerDelta -= delta;
	m_timeDelta += delta;

	if (m_timeDelta >= 10000.f) {

		m_timeToSpawn -= 100.f;
		m_timeDelta = 0.f;
	}

	if (m_spawnerDelta > 0) return;

	spawnEnemy();
	m_spawnerDelta = m_timeToSpawn;
}
