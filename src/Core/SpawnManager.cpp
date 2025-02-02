#include "Core/SpawnManager.h"
#include <random>

SpawnManager* SpawnManager::s_instance{ nullptr };

void SpawnManager::initializeSpawners(Player* target)
{
	std::vector<sf::Vector2f> spawnPositions = {
		{-2.f, -2.f},
		{1921.f, -2.f},
		{-2.f, 1081.f},
		{1921.f, 1081.f}
	};

	static std::random_device rd;
	static std::mt19937 gen(rd());

	for (int i = 0; i < m_spawnersAmount; i++) {
		Spawner* spawner = new Spawner();

		m_spawners.push_back(spawner);
		std::uniform_real_distribution<float> dist(2000, 5000);
		m_spawners.back()->initialize(spawnPositions[i % spawnPositions.size()], target, dist(gen));
	}
}

void SpawnManager::update(float deltaMiliseconds)
{
	for (Spawner* spawner : m_spawners) spawner->update(deltaMiliseconds);
}