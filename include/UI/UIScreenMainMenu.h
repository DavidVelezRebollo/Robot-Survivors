#pragma once

#include <SFML/Graphics.hpp>
#include <UI/UIManager.h>

class UIScreenMainMenu {
public:

	~UIScreenMainMenu() = default;

	void init(float screenWidth, float screenHeight);

	void render(sf::RenderWindow& window);
	void update(float delta);
private:
	bool checkMouseOnButton(sf::Vector2i mousePos, sf::RectangleShape button) const 
	{ return button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)); }

	bool m_close{ false };

	sf::Font m_font;
	sf::Sprite m_background;

	sf::Text m_title;

	sf::RectangleShape m_playButton;
	sf::Text m_playText;

	sf::RectangleShape m_exitButton;
	sf::Text m_exitText;
};