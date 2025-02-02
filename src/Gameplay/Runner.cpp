#include "Gameplay/Runner.h"

void Runner::enemyBehaviour(float delta) {
	chaseTarget(delta);
}

void Runner::chaseTarget(float delta)
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

void Runner::initStats()
{
	m_maxHp = 1.5f;
	m_damage = 2.f;
	m_speed = 250.f;
	m_experience = 10.f;
}
