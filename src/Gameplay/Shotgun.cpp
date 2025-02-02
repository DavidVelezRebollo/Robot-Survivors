#include "Gameplay/Shotgun.h"
#include "Core/BulletPool.h"

void Shotgun::shoot(sf::Vector2f position)
{
	sf::Vector2f pos = position;

	sf::Vector2f direction = sf::Vector2f(sf::Mouse::getPosition()) - pos;
	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= magnitude;

	for (int i = 0; i < m_numPellets; i++) {
		float offsetX = (rand() % 1000 / 1000.f) * spread - (spread / 2.f);
		float offsetY = (rand() % 1000 / 1000.f) * spread - (spread / 2.f);

		sf::Vector2f pelletPosition = position + sf::Vector2f(offsetX, offsetY);

		Projectile* projectile = BulletPool::getInstance()->getBullet("../Data/Images/Weapons/pellet.png", pelletPosition, direction, m_damage, false);
	}

	SoundManager::getInstance()->shootgunShoot();
	resetDelta();
}

void Shotgun::init()
{
	m_name = "Escopeta";
	m_weaponSprite = AssetManager::getInstance()->loadTexture("../Data/Images/Weapons/Shotgun.png");

	m_damage = 0.5f;
	m_range = 3.f;
	m_shootCooldown = 650.f;
	m_level = 1;
}

void Shotgun::levelUp(int level)
{
	m_level = level;

	m_damage = 0.1f + (m_level - 1) * 0.05f;
	m_shootCooldown = 650.f + pow(0.9f, m_level - 1);
}

float Shotgun::getLevelShootCooldown(int level)
{
	return (650.f + pow(0.9f, m_level - 1)) / 1000.f;
}

float Shotgun::getLevelDamage(int level)
{
	return 0.1f + (m_level - 1) * 0.05f;
}
