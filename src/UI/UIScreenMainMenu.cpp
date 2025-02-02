#include "UI/UIScreenMainMenu.h"

void UIScreenMainMenu::init(float screenWidth, float screenHeight)
{
	m_font.loadFromFile("../Data/NotJamUI15.ttf");

	sf::Texture* tex = AssetManager::getInstance()->loadTexture("../Data/Images/MainMenuBG.png");
	m_background.setTexture(*tex);
	m_background.setScale(1.f, 1.04f);

	m_title.setFont(m_font);
	m_title.setString("Robot Survivors");
	m_title.setFillColor(sf::Color(220, 190, 194));
	m_title.setOutlineColor(sf::Color(60, 17, 45));
	m_title.setOutlineThickness(3);
	m_title.setCharacterSize(100);
	m_title.setOrigin(m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().height / 2.0f);
	m_title.setPosition(screenWidth / 2, screenHeight * 0.2f);

	m_playButton.setSize(sf::Vector2f{ 500.f, 100.f });
	m_playButton.setFillColor(sf::Color(49, 40, 45, 200));
	m_playButton.setOutlineColor(sf::Color(60, 17, 45));
	m_playButton.setOutlineThickness(3);
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2.0f, m_playButton.getLocalBounds().height / 2.0f);
	m_playButton.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);

	m_playText.setFont(m_font);
	m_playText.setString("Jugar");
	m_playText.setFillColor(sf::Color(220, 190, 194));
	m_playText.setOutlineColor(sf::Color(60, 17, 45));
	m_playText.setOutlineThickness(3);
	m_playText.setCharacterSize(50);
	sf::FloatRect textBounds = m_playText.getLocalBounds();
	m_playText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_playText.setPosition(m_playButton.getPosition());

	m_exitButton.setSize(sf::Vector2f{ 500.f, 100.f });
	m_exitButton.setFillColor(sf::Color(49, 40, 45, 200));
	m_exitButton.setOutlineColor(sf::Color(60, 17, 45));
	m_exitButton.setOutlineThickness(3);
	m_exitButton.setOrigin(m_playButton.getLocalBounds().width / 2.0f, m_playButton.getLocalBounds().height / 2.0f);
	m_exitButton.setPosition(screenWidth / 2.0f, screenHeight * 0.7f);

	m_exitText.setFont(m_font);
	m_exitText.setString("Salir");
	m_exitText.setFillColor(sf::Color(220, 190, 194));
	m_exitText.setOutlineColor(sf::Color(60, 17, 45));
	m_exitText.setOutlineThickness(3);
	m_exitText.setCharacterSize(50);
	textBounds = m_exitText.getLocalBounds();
	m_exitText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_exitText.setPosition(m_exitButton.getPosition());
}

void UIScreenMainMenu::render(sf::RenderWindow& window)
{
	if (m_close) {
		window.close();
		return;
	}

	window.draw(m_background);
	window.draw(m_title);
	window.draw(m_playButton);
	window.draw(m_playText);
	window.draw(m_exitButton);
	window.draw(m_exitText);
}

void UIScreenMainMenu::update(float delta)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) return;

	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (checkMouseOnButton(mousePos, m_playButton)) {
		UIManager::getInstance()->goToGame();
	}
	else if (checkMouseOnButton(mousePos, m_exitButton)) {
		m_close = true;
	}
}
