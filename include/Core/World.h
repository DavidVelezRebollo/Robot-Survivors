#pragma once

#include <cstdint>

#include <Core/BulletPool.h>
#include <Core/SpawnManager.h>
#include <Core/WeaponManager.h>
#include <Core/EnemyPool.h>
#include <Core/CollisionManager.h>
#include <Core/GameManager.h>

class Player;

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;
class ObjectLayer;

class World
{
	public:

		~World();

		bool load();
		void unload();
		bool initialized() const { return m_isInitialized; }

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);

	private:
		bool m_isInitialized{ false };

		Player* m_player{ nullptr };

		SpawnManager* m_spawners{ nullptr };
		BulletPool* m_bullets{ nullptr };
		EnemyPool* m_enemies{ nullptr };
		WeaponManager* m_weapons{ nullptr };
		CollisionManager* m_collisionManager{ nullptr };
		
		tmx::Map* m_map{ nullptr };
		MapLayer* m_layerZero{ nullptr };
		MapLayer* m_layerOne{ nullptr };
		MapLayer* m_layerTwo{ nullptr };
};