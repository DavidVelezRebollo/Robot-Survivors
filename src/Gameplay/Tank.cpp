#include "Gameplay/Tank.h"

void Tank::enemyBehaviour(float delta)
{
	chaseTarget(delta);
}

void Tank::chaseTarget(float delta)
{
	sf::Vector2f enemyPos = getPosition();
	sf::Vector2f targetPos = m_target->getPosition();

	sf::Vector2f direction = targetPos - enemyPos;
	float distanceSquared = direction.x * direction.x + direction.y * direction.y;
	float threshold = 50.0f;
	if (distanceSquared <= threshold * threshold) return;

	float lenght = std::sqrt(distanceSquared);
	if (lenght != 0) {
		direction.x /= lenght;
		direction.y /= lenght;
	}

	sf::Vector2f movement = direction * m_speed * (delta / 1000.f);
	m_sprite.move(movement);
	m_position = m_sprite.getPosition();

	float angle = std::atan2(direction.y, direction.x) * 180.f / 3.141519f;
	m_sprite.setRotation(angle);
}

void Tank::initStats()
{
	m_maxHp = 4.f;
	m_damage = 5.f;
	m_speed = 50.f;
	m_experience = 50.f;
}
