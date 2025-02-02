#include "UI/UIManager.h"

UIManager* UIManager::s_instance{ nullptr };

void UIManager::init(float screenWidth, float screenHeight)
{
	m_width = screenWidth;
	m_height = screenHeight;

	m_hud = new HUD();
	m_hud->init(m_width, m_height);
}

void UIManager::goToGame()
{
	m_onMainMenu = false;
}

void UIManager::returnToMainMenu()
{
	m_onMainMenu = true;
}

void UIManager::update(float delta) {
	if (m_onMainMenu) { return; }

	m_hud->update(delta);
	if (m_hud->returnToMenu()) {
		returnToMainMenu();
		m_hud->reset();
	}
}

void UIManager::render(sf::RenderWindow& window) {
	if (m_onMainMenu) { return; }

	m_hud->render(window);
}
