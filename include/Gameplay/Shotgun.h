#pragma once

#include "Gameplay/Weapon.h"

class Shotgun : public Weapon {
	public:

		void shoot(sf::Vector2f position) override;
		void init() override;
		void levelUp(int level) override;

		float getLevelShootCooldown(int level) override;
		float getLevelDamage(int level) override;
	private:

		const int m_numPellets = 3;
		const float spread = 90.f;
};