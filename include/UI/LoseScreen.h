#pragma once

#include <SFML/Graphics.hpp>
#include <Core/GameManager.h>

class LoseScreen {
public:
	~LoseScreen() = default;

	void init(float screenWidth, float screenHeight);
	bool returnToMenu() const { return m_returnToMenu; }
	void resetReturnToMenu() { m_returnToMenu = false; }
	void setScore(float score);

	void render(sf::RenderWindow& window);
	void update(float delta);
private:
	bool checkMouseOnButton(sf::Vector2i mousePos) { return m_quitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); }

	bool m_returnToMenu{ false };

	float m_screenWidth;
	float m_screenHeight;

	sf::Font m_font;

	sf::RectangleShape m_background;
	sf::Text m_text;

	sf::Text m_scoreText;

	sf::RectangleShape m_quitButton;
	sf::Text m_quitText;
};