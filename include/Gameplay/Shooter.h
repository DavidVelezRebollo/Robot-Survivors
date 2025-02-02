#pragma once

#include <Core/BulletPool.h>
#include <Gameplay/Enemy.h>

class Shooter : public Enemy {
public:

	void enemyBehaviour(float delta) override;

protected:

	void chaseAndStop(float delta);
	void shoot();
	void initStats() override;

	sf::Vector2f m_direction;

	float m_distanceToTarget{ 0.f };
	float m_shootCooldown{ 0.f };
	float m_shootDelta{ 0.f };
};