#include "UI/LoseScreen.h"

#include "iostream"
#include "cmath"

void LoseScreen::init(float screenWidth, float screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_font.loadFromFile("../Data/NotJamUI15.ttf");

	m_background.setFillColor(sf::Color{100, 0, 0, 200});
	m_background.setSize(sf::Vector2f{ screenWidth, screenHeight });
	m_background.setOrigin(m_background.getLocalBounds().width / 2.0f, m_background.getLocalBounds().height / 2.0f);
	m_background.setPosition(sf::Vector2f{ screenWidth / 2, screenHeight / 2 });

	m_text.setFont(m_font);
	m_text.setString("¡Has perdido!");
	m_text.setFillColor(sf::Color(220, 190, 194));
	m_text.setCharacterSize(75);
	m_text.setOutlineColor(sf::Color(60, 17, 45));
	m_text.setOutlineThickness(3);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
	m_text.setPosition(screenWidth / 2.0f, screenHeight * 0.1f);

	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color(220, 190, 194));
	m_scoreText.setOutlineColor(sf::Color(60, 17, 45));
	m_scoreText.setOutlineThickness(3);
	m_scoreText.setCharacterSize(50);

	m_quitButton.setFillColor(sf::Color{ 0, 0, 0, 128 });
	m_quitButton.setSize(sf::Vector2f{ 500.f, 100.f });
	m_quitButton.setOrigin(m_quitButton.getLocalBounds().width / 2.0f, m_quitButton.getLocalBounds().height / 2.0f);
	m_quitButton.setOutlineColor(sf::Color::White);
	m_quitButton.setOutlineThickness(3);
	m_quitButton.setPosition(screenWidth * 0.5f, screenHeight * 0.6f);

	m_quitText.setFont(m_font);
	m_quitText.setString("Volver al menú");
	m_quitText.setColor(sf::Color::White);
	m_quitText.setCharacterSize(45);
	m_quitText.setOutlineColor(sf::Color::Black);
	m_quitText.setOutlineThickness(3);

	sf::FloatRect textBounds = m_quitText.getLocalBounds();
	m_quitText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_quitText.setPosition(m_quitButton.getPosition());
}

void LoseScreen::setScore(float score)
{
	int rounded = std::floor(score);
	std::cout << rounded << std::endl;

	int defeatedEnemies = GameManager::getInstance()->getEnemiesDefeated();
	int time = GameManager::getInstance()->getTime();

	m_scoreText.setString("Puntuación total: " + std::to_string(rounded) + "\nEnemigos derrotados: " + std::to_string(defeatedEnemies) + ".\nTiempo aguantado: " + std::to_string(time) + "seg.");
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2.0f, m_scoreText.getLocalBounds().height / 2.0f);
	m_scoreText.setPosition(m_screenWidth * 0.5f, m_screenHeight * 0.3);
}

void LoseScreen::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_text);
	window.draw(m_scoreText);
	window.draw(m_quitButton);
	window.draw(m_quitText);
}

void LoseScreen::update(float delta)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) || !checkMouseOnButton(mousePos)) return;

	m_returnToMenu = true;
	GameManager::getInstance()->reset();
}
