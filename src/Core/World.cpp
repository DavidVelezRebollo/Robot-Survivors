#include <Core/AssetManager.h>
#include <Core/BulletPool.h>
#include <Core/World.h>
#include <Core/WeaponManager.h>
#include <Core/EnemyPool.h>

#include <Gameplay/GameObject.h>
#include <Gameplay/Player.h>

#include <Render/MapLayer.h>
#include <Render/ObjectLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>

World::~World()
{
	unload();
}

bool World::load()
{
	constexpr float millisecondsToSeconds = 1 / 1000.f;

	m_bullets = BulletPool::getInstance();
	m_weapons = WeaponManager::getInstance();
	m_weapons->init();

	m_spawners = SpawnManager::getInstance();

	m_collisionManager = CollisionManager::getInstance();

	m_enemies = EnemyPool::getInstance();

	m_player = new Player();
	m_player->init(millisecondsToSeconds);

	m_spawners->initializeSpawners(m_player);

	m_map = new tmx::Map();
	m_map->load("../Data/Levels/mapa.tmx");
	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);
	m_layerTwo = new MapLayer(*m_map, 2);

	m_isInitialized = true;

	return m_isInitialized;
}

void World::unload() {
	delete m_player;
	m_player = nullptr;

	delete m_layerZero;
	m_layerZero = nullptr;

	delete m_map;
	m_map = nullptr;

	delete m_bullets;
	m_bullets = nullptr;

	delete m_spawners;
	m_spawners = nullptr;

	delete m_weapons;
	m_weapons = nullptr;

	delete m_enemies;
	m_enemies = nullptr;

	delete m_collisionManager;
	m_collisionManager = nullptr;

	m_isInitialized = false;
}

void World::update(uint32_t deltaMilliseconds)
{
	if (GameManager::getInstance()->gamePaused()) return;

	// Managers
	m_bullets->update(deltaMilliseconds);
	m_weapons->update(deltaMilliseconds);
	m_spawners->update(deltaMilliseconds);

	// Map
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));

	// Actors
	m_player->update(deltaMilliseconds);
	m_enemies->update(deltaMilliseconds);

	// Collisions
	m_collisionManager->update(deltaMilliseconds);
}

void World::render(sf::RenderWindow& window)
{
	window.draw(*m_layerZero);
	window.draw(*m_layerOne);
	window.draw(*m_layerTwo);

	m_player->render(window);
	m_bullets->render(window);
	m_enemies->render(window);
}