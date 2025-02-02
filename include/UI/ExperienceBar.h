#pragma once

#include <SFML/Graphics.hpp>

class ExperienceBar {
public:
	~ExperienceBar() = default;

	void init(float posX, float posY, float screenWidth, float screenHeight);

	void updateExperience(float fillPercentage) { m_expFill.setSize(sf::Vector2f(m_expBackground.getSize().x * fillPercentage, 20.f)); }
	void reset() { m_expFill.setSize(sf::Vector2f( 0.f, m_expFill.getSize().y )); }

	void render(sf::RenderWindow& window);
private:
	sf::RectangleShape m_expBackground;
	sf::RectangleShape m_expFill;
};