#pragma once

#include "Gameplay/Weapon.h"

class Pistol : public Weapon {
	public:

		void shoot(sf::Vector2f position) override;
		void init() override;
		void levelUp(int level) override;

		float getLevelShootCooldown(int level) override;
		float getLevelDamage(int level) override;
};