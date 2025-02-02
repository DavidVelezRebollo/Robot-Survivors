#include "UI/ExperienceBar.h"

void ExperienceBar::init(float posX, float posY, float screenWidth, float screenHeight)
{
	m_expBackground.setPosition(sf::Vector2(posX, posY));
	m_expBackground.setSize(sf::Vector2f(screenWidth * 0.15f, 20));
	m_expBackground.setFillColor(sf::Color(21, 5, 16));
	m_expBackground.setOutlineColor(sf::Color( 60, 17, 45 ));
	m_expBackground.setOutlineThickness(2.f);

	m_expFill.setPosition(sf::Vector2(posX, posY));
	m_expFill.setSize(sf::Vector2f(0, screenHeight * 0.02f));
	m_expFill.setFillColor(sf::Color( 156, 186, 33 ));
}

void ExperienceBar::render(sf::RenderWindow& window)
{
	window.draw(m_expBackground);
	window.draw(m_expFill);
}
