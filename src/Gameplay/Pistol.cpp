#include "Gameplay/Pistol.h"
#include "Gameplay/Projectile.h"
#include "Core/BulletPool.h"

#include "SFML/Graphics.hpp"

void Pistol::shoot(sf::Vector2f position)
{
	sf::Vector2f pos = position;

	sf::Vector2f direction = sf::Vector2f(sf::Mouse::getPosition()) - pos;
	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= magnitude;

	Projectile* projectile = BulletPool::getInstance()->getBullet("../Data/Images/Weapons/bullet.png", pos, direction, m_damage, false);
	SoundManager::getInstance()->pistolShoot();
	resetDelta();
}

void Pistol::levelUp(int level) 
{
	m_level = level;

	m_damage = 0.5f + (m_level - 1) * 0.1f;
	m_shootCooldown = 200.f;
}

float Pistol::getLevelShootCooldown(int level)
{
	return getShootCooldown();
}

float Pistol::getLevelDamage(int level)
{
	return 0.5f + (m_level - 1) * 0.1f;
}

void Pistol::init() 
{
	m_weaponSprite = AssetManager::getInstance()->loadTexture("../Data/Images/Weapons/Pistol.png");
	m_name = "Metralleta";

	m_damage = 0.7f;
	m_range = 10.f;
	m_shootCooldown = 200.f;
}
