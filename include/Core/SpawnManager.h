#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/Spawner.h>
#include <Core/EnemyPool.h>

class SpawnManager {
	public:

		~SpawnManager() {
			for (Spawner* spawner : m_spawners) {
				delete spawner;
				spawner = nullptr;
			}

			m_spawners.clear();
			s_instance = nullptr;
		}

		static SpawnManager* getInstance() {
			if (s_instance == nullptr) {
				s_instance = new SpawnManager();
			}

			return s_instance;
		}

		void initializeSpawners(Player* target);

		void update(float deltaMiliseconds);
	private:
		static SpawnManager* s_instance;

		const int m_spawnersAmount = 4;
		std::vector<Spawner*> m_spawners;
};