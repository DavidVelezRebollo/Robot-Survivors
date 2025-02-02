#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/Weapon.h>

#include <sstream>
#include <iomanip>
#include <iostream>

class WeaponCard {
public:

	~WeaponCard() = default;

	void updateCard(Weapon* weapon, int level);
	void setupCard(float xPos, float yPos);
	bool checkMouseOnCard(sf::Vector2i mousePos) const { return m_background.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); }

	void render(sf::RenderWindow& window);
private:
	std::string floatToString(float value);

	sf::Font m_font;

	sf::RectangleShape m_background;
	sf::Sprite m_weaponSprite;
	sf::Text m_weaponText;
	sf::Text m_weaponLevelText;
	sf::Text m_weaponStats;
};