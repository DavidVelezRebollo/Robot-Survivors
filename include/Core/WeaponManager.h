#pragma once

#include "Gameplay/Weapon.h"
#include "Gameplay/Pistol.h"
#include "Gameplay/Raygun.h"
#include "Gameplay/Shotgun.h"

class WeaponManager {
	public:
		~WeaponManager() {
			for (Weapon* weapon : m_weapons) {
				delete weapon;
				weapon = nullptr;
			}

			m_instance = nullptr;
		}

		static WeaponManager* getInstance();
		void init();

		Weapon* getCurrentWeapon();
		Weapon* getRandomWeapon();

		void changeWeapon(Weapon* newWeapon, int newLevel);
		void levelUpAllWeapons(int level);

		void update(float delta);
	private:

		Weapon* m_currentWeapon;

		Pistol* m_pistol;
		Raygun* m_raygun;
		Shotgun* m_shotgun;

		std::vector<Weapon*> m_weapons;

		static WeaponManager* m_instance;
};