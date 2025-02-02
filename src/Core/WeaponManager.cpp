#include "Core/WeaponManager.h"
#include "Gameplay/Pistol.h"
#include <random>

WeaponManager* WeaponManager::m_instance{ nullptr };

WeaponManager* WeaponManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new WeaponManager();
	}
	return m_instance;
}

void WeaponManager::init()
{
	m_pistol = new Pistol();
	m_pistol->init();
	m_weapons.push_back(m_pistol);

	m_shotgun = new Shotgun();
	m_shotgun->init();
	m_weapons.push_back(m_shotgun);
	
	m_raygun = new Raygun();
	m_raygun->init();
	m_weapons.push_back(m_raygun);

	// m_bomb = new Bomb();

	m_currentWeapon = m_pistol;
}

Weapon* WeaponManager::getCurrentWeapon()
{
	return m_currentWeapon;
}

Weapon* WeaponManager::getRandomWeapon()
{
	Weapon* weaponToGet = nullptr;
	static std::random_device rd;
	static std::mt19937 gen(rd());

	do {
		std::uniform_real_distribution<float> dist(0, 3);
		weaponToGet = m_weapons[dist(gen)];
	} while (weaponToGet == m_currentWeapon);

	return weaponToGet;
}

void WeaponManager::changeWeapon(Weapon* newWeapon, int newLevel)
{
	if (m_currentWeapon == newWeapon) {
		levelUpAllWeapons(m_currentWeapon->getLevel() + 1);
		return;
	}

	m_currentWeapon = newWeapon;
	levelUpAllWeapons(newLevel);
}

void WeaponManager::update(float delta) {
	if (m_currentWeapon == nullptr) return;

	m_currentWeapon->update(delta);
}

void WeaponManager::levelUpAllWeapons(int level) {
	for (Weapon* weapon : m_weapons) weapon->levelUp(level);
}