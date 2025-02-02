#pragma once

#include <cstdint>
#include <string>

#include <UI/UIScreenMainMenu.h>
#include <UI/UIManager.h>

#include <Core/World.h>
#include <Core/AssetManager.h>
#include <Core/SoundManager.h>
#include <Core/GameManager.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace sf
{
	class RenderWindow;
}

class World;

class Game
{
	public:

		struct GameCreateInfo
		{
			std::string gameTitle;
			uint32_t screenWidth;
			uint32_t screenHeight;
			uint32_t frameRateLimit;
		};

		~Game();

		bool init(GameCreateInfo& createInfo);

		bool isRunning() const;

		void update(uint32_t deltaMilliseconds);
		void render();

	private:

		sf::RenderWindow* m_window{ nullptr };
		GameManager* m_gameManager{ nullptr };
		SoundManager* m_soundManager{ nullptr };
		World* m_world{ nullptr };
		UIManager* m_uiManager{ nullptr };
		UIScreenMainMenu* m_mainMenu{ nullptr };
};