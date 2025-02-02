#include "UI/HUD.h"
#include <Core/GameManager.h>

#include <iostream>
#include <random>

void HUD::init(float screenWidth, float screenHeight)
{
	float posX = screenWidth * 0.01f, posY = screenHeight * 0.05f;
	m_screenWidth = screenWidth; 
	m_screenHeight = screenHeight;

	m_loseScreen = new LoseScreen();
	m_loseScreen->init(screenWidth, screenHeight);

	m_font.loadFromFile("../Data/NotJamUI15.ttf");

	initTitleText();

	m_experienceBar = new ExperienceBar();
	m_experienceBar->init(posX, posY, screenWidth, screenHeight);

	posY = screenHeight * 0.02f;

	m_hpBar = new HpBar();
	m_hpBar->init(posX, posY, screenWidth);

	m_card1 = new WeaponCard();
	m_card2 = new WeaponCard();

	m_card1->setupCard(m_screenWidth * 0.28f, m_screenHeight * 0.5f);
	m_card2->setupCard(m_screenWidth * 0.68f, m_screenHeight * 0.5f);

	m_initialized = true;
}

void HUD::addExperience(float amount, float total)
{
	m_experienceBar->updateExperience(amount / total);
}

void HUD::onLevelUp()
{
	GameManager::getInstance()->pauseGame();

	static std::random_device rd;
	static std::mt19937 gen(rd());

	m_weapon = WeaponManager::getInstance()->getCurrentWeapon();
	m_weapon2 = WeaponManager::getInstance()->getRandomWeapon();

	std::uniform_real_distribution<float> dist(2, 3);
	m_weaponLevel = m_weapon->getLevel() + 1;
	m_weapon2Level = m_weapon2->getLevel() + dist(gen);

	m_card1->updateCard(m_weapon, m_weaponLevel);
	m_card2->updateCard(m_weapon2, m_weapon2Level);

	m_showingCards = true;
}

void HUD::onHpChange(float healthPercentage)
{
	m_hpBar->updateBar(healthPercentage);
}

void HUD::onDie()
{
	GameManager::getInstance()->pauseGame();
	m_loseScreen->setScore(GameManager::getInstance()->calculateFinalScore());
	m_dead = true;
}

void HUD::reset()
{
	m_dead = false;
	m_returnToMenu = false;
	m_showingCards = false;
	m_initialized = false;

	m_hpBar->reset(m_screenWidth);
	m_experienceBar->reset();
}

void HUD::update(float delta)
{
	if (m_dead) {
		m_loseScreen->update(delta);
		if (m_loseScreen->returnToMenu()) {
			m_returnToMenu = true;
			m_loseScreen->resetReturnToMenu();
		}
		return;
	}

	if (!m_showingCards) return;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) return;

	m_mousePos = sf::Mouse::getPosition();

	if (m_card1->checkMouseOnCard(m_mousePos)) selectWeapon(m_weapon, m_weaponLevel);
	else if (m_card2->checkMouseOnCard(m_mousePos)) selectWeapon(m_weapon2, m_weapon2Level);
}

void HUD::render(sf::RenderWindow& window)
{
	if (m_dead) {
		m_loseScreen->render(window);
		return;
	}

	m_experienceBar->render(window);
	m_hpBar->render(window);

	if (!m_showingCards) return;

	m_card1->render(window);
	m_card2->render(window);

	window.draw(m_titleText);
}

void HUD::initTitleText()
{
	m_titleText.setFont(m_font);
	m_titleText.setFillColor(sf::Color(220, 190, 194));
	m_titleText.setOutlineColor(sf::Color(60, 17, 45));
	m_titleText.setOutlineThickness(3);
	m_titleText.setString("Elige un arma");
	m_titleText.setOrigin(sf::Vector2f{ m_titleText.getLocalBounds().width / 2.0f, m_titleText.getLocalBounds().height / 2.0f });
	m_titleText.setPosition(sf::Vector2f{ m_screenWidth * 0.46f, 150.f });
	m_titleText.setCharacterSize(40);
}

void HUD::selectWeapon(Weapon* weapon, int level) {
	WeaponManager::getInstance()->changeWeapon(weapon, level);
	GameManager::getInstance()->resumeGame();
	m_showingCards = false;
}
