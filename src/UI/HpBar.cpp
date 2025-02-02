#include "UI/HpBar.h"

void HpBar::init(float posX, float posY, float screenWidth)
{
	m_hpBackground.setPosition(sf::Vector2f{ posX, posY });
	m_hpBackground.setSize(sf::Vector2f{ screenWidth * 0.3f, 20 });
	m_hpBackground.setFillColor(sf::Color( 21, 5, 16 ));
	m_hpBackground.setOutlineColor(sf::Color( 60, 17, 45 ));
	m_hpBackground.setOutlineThickness(2.f);

	m_hpBar.setPosition(sf::Vector2f{ posX, posY });
	m_hpBar.setSize(sf::Vector2f(screenWidth * 0.3f, 20));
	m_hpBar.setFillColor(sf::Color( 186, 33, 70 ));

	m_hpSize = m_hpBackground.getSize().x;
}

void HpBar::reset(float screenWidth)
{
	m_hpBar.setSize(sf::Vector2f(screenWidth * 0.3f, 20));
}

void HpBar::render(sf::RenderWindow& window)
{
	window.draw(m_hpBackground);
	window.draw(m_hpBar);
}
