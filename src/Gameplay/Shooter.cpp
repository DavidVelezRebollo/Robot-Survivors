#include "Gameplay/Shooter.h"

void Shooter::enemyBehaviour(float delta)
{
	chaseAndStop(delta);
}

void Shooter::chaseAndStop(float delta)
{
	if (m_shootDelta > 0.f) {
		m_shootDelta -= delta;
	}

	sf::Vector2f enemyPos = getPosition();
	sf::Vector2f targetPos = m_target->getPosition();

	m_direction = targetPos - enemyPos;
	float distanceSquared = m_direction.x * m_direction.x + m_direction.y * m_direction.y;
	if (distanceSquared <= m_distanceToTarget * m_distanceToTarget) {
		shoot();
		return;
	}

	float lenght = std::sqrt(distanceSquared);
	if (lenght != 0) {
		m_direction.x /= lenght;
		m_direction.y /= lenght;
	}

	sf::Vector2f movement = m_direction * m_speed * (delta / 1000.f);
	m_sprite.move(movement);
	m_position = m_sprite.getPosition();

	float angle = std::atan2(m_direction.y, m_direction.x) * 180.f / 3.141519f;
	m_sprite.setRotation(angle);
}

void Shooter::shoot()
{
	if (m_shootDelta > 0.f) return;

	BulletPool::getInstance()->getBullet("../Data/Images/Weapons/bullet.png", getPosition(), m_direction, m_damage, true);
	m_shootDelta = m_shootCooldown;
}

void Shooter::initStats()
{
	m_maxHp = 0.7f;
	m_damage = 3.f;
	m_speed = 125.f;
	m_experience = 50.f;

	m_distanceToTarget = 300.f;
	m_shootCooldown = 1000.f;
	m_shootDelta = m_shootCooldown;
}
