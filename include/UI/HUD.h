#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/Weapon.h>
#include <Core/WeaponManager.h>

#include <UI/WeaponCard.h>
#include <UI/ExperienceBar.h>
#include <UI/HpBar.h>
#include <UI/LoseScreen.h>

class HUD {
public:

	~HUD() {
		delete m_card1;
		m_card1 = nullptr;
		delete m_card2;
		m_card2 = nullptr;
		delete m_experienceBar;
		m_experienceBar = nullptr;
		delete m_hpBar;
		m_hpBar = nullptr;
		delete m_loseScreen;
		m_loseScreen = nullptr;

		m_weapon = nullptr;
		m_weapon2 = nullptr;
	}

	void init(float screenWidth, float screenHeight);

	void addExperience(float amount, float total);
	void onLevelUp();
	void onHpChange(float healthPercentage);
	void onDie();
	bool returnToMenu() const { return m_returnToMenu; }
	void reset();

	void update(float delta);
	void render(sf::RenderWindow& window);

private:

	void initTitleText();
	void selectWeapon(Weapon* weapon, int level);

	bool m_initialized{ false };
	bool m_showingCards{ false };
	bool m_dead{ false };
	bool m_returnToMenu{ false };

	sf::Font m_font;

	sf::Vector2i m_mousePos;

	ExperienceBar* m_experienceBar{ nullptr };
	HpBar* m_hpBar{ nullptr };

	LoseScreen* m_loseScreen{ nullptr };

	Weapon* m_weapon{ nullptr };
	Weapon* m_weapon2{ nullptr };

	int m_weaponLevel{ 0 };
	int m_weapon2Level{ 0 };

	WeaponCard* m_card1{ nullptr };
	WeaponCard* m_card2{ nullptr };

	sf::Text m_titleText;

	float m_screenWidth{ 0.f };
	float m_screenHeight{ 0.f };
};