#pragma once

#include <UI/HUD.h>

#include <SFML/Graphics.hpp>

class UIManager {
public:

	~UIManager() {
		delete m_hud;
		m_hud = nullptr;

		s_instance = nullptr;
	}

	static UIManager* getInstance() {
		if (s_instance == nullptr) {
			s_instance = new UIManager;
		}

		return s_instance;
	}

	void init(float screenWidth, float screenHeight);
	HUD* getHUD() { return m_hud; };
	void goToGame();
	void returnToMainMenu();
	bool onMainMenu() { return m_onMainMenu; }

	float geWidth() const { return m_width; }
	float getHeight() const { return m_height; }
	
	void update(float delta);
	void render(sf::RenderWindow& window);
private:
	static UIManager* s_instance;

	HUD* m_hud{ nullptr };

	float m_width{ 0.f };
	float m_height{ 0.f };

	bool m_onMainMenu{ true };
};