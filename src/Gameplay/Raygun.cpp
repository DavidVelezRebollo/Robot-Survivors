#include "Gameplay/Raygun.h"
#include "Gameplay/Projectile.h"
#include "Core/BulletPool.h"

void Raygun::shoot(sf::Vector2f position)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f pos = position;

	sf::Vector2f direction = sf::Vector2f(sf::Mouse::getPosition()) - pos;
	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= magnitude;

	Projectile* projectile = BulletPool::getInstance()->getBullet("../Data/Images/Weapons/ray.png", pos, direction, m_damage, false, true);
	SoundManager::getInstance()->raygunShoot();
	resetDelta();
}

void Raygun::init()
{
	m_name = "Pistola de rayos";
	m_weaponSprite = AssetManager::getInstance()->loadTexture("../Data/Images/Weapons/Raygun.png");

	m_damage = 0.25f;
	m_shootCooldown = 400.f;
}

void Raygun::levelUp(int level)
{
	m_level = level;

	m_damage = 0.1f + (level - 1) * 0.1f;
	m_shootCooldown = 400.f + pow(0.95f, level - 1);
}

float Raygun::getLevelShootCooldown(int level)
{
	return (400.f + pow(0.95f, level - 1)) / 1000.f;
}

float Raygun::getLevelDamage(int level)
{
	return 0.1f + (level - 1) * 0.1f;
}
