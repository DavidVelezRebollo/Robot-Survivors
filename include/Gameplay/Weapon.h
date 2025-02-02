#pragma once

#include "SFML/Graphics.hpp"
#include "Core/AssetManager.h"
#include "Core/SoundManager.h"

class Weapon {
	public:
		~Weapon() {
			m_weaponSprite = nullptr;
		}

		std::string getName() const { return m_name; }
		sf::Texture* getSprite() const { return m_weaponSprite; }
		bool canShoot() const { return m_deltaShoot <= 0; }
		float getRange() const { return m_range; }
		float getDeltaShoot() const { return m_deltaShoot; }
		float getShootCooldown() { return m_shootCooldown / 1000.f; }
		float getDamage() const { return m_damage; }
		int getLevel() const { return m_level; }
		void resetDelta() { m_deltaShoot = m_shootCooldown; }

		void update(float delta);

		virtual void shoot(sf::Vector2f position) = 0;
		virtual void init() = 0;
		virtual void levelUp(int level) = 0;

		virtual float getLevelShootCooldown(int level) = 0;
		virtual float getLevelDamage(int level) = 0;

	protected:
		sf::Texture* m_weaponSprite;
		std::string m_name;

		float m_range{ 0.f };
		float m_shootCooldown{ 0.f };
		float m_deltaShoot{ 0.f };
		float m_damage{ 0.f };

		int m_level{ 1 };
};