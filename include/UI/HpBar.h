#pragma once

#include <SFML/Graphics.hpp>

class HpBar {
public:

	~HpBar() = default;

	void init(float posX, float posY, float screenWidth);
	void updateBar(float healthPercentage) { m_hpBar.setSize(sf::Vector2f{ m_hpSize * healthPercentage, m_hpBar.getSize().y }); }
	void reset(float screenWidth);

	void render(sf::RenderWindow& window);
private:

	sf::RectangleShape m_hpBackground;
	sf::RectangleShape m_hpBar;
	float m_hpSize{ 0 };
};