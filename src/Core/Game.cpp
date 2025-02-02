#include <cassert>
#include <Core/Game.h>


bool Game::init(GameCreateInfo& createInfo)
{
	assert(m_window == nullptr && m_world == nullptr && "Game is already initialized, we are about to leak memory");

	m_window = new sf::RenderWindow({ createInfo.screenWidth, createInfo.screenHeight }, createInfo.gameTitle);
	m_window->setFramerateLimit(createInfo.frameRateLimit);

	m_gameManager = GameManager::getInstance();

	m_soundManager = SoundManager::getInstance();
	m_soundManager->init();
	m_soundManager->playMusic();

	m_mainMenu = new UIScreenMainMenu();
	m_mainMenu->init(createInfo.screenWidth, createInfo.screenHeight);

	m_world = new World();

	m_uiManager = UIManager::getInstance();
	m_uiManager->init(createInfo.screenWidth, createInfo.screenHeight);

	return true;
}

Game::~Game()
{
	AssetManager::getInstance()->unloadTextures();
	if (m_world->initialized()) m_world->unload();

	delete m_window;

	delete m_gameManager;
	m_gameManager = nullptr;
	delete m_soundManager;
	m_soundManager = nullptr;
	delete m_mainMenu;
	m_mainMenu = nullptr;
	delete m_world;
	m_world = nullptr;
}

bool Game::isRunning() const 
{ 
	return m_window->isOpen(); 
}

void Game::update(uint32_t deltaMilliseconds)
{
	for (auto event = sf::Event(); m_window->pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}

	m_gameManager->update(deltaMilliseconds);

	if (m_uiManager->onMainMenu()) m_mainMenu->update(deltaMilliseconds);
	else {
		if (m_world->initialized()) m_world->update(deltaMilliseconds);
	}

	m_uiManager->update(deltaMilliseconds);
}

void Game::render()
{
	m_window->clear();

	if (m_uiManager->onMainMenu()) {
		if (m_world->initialized()) {
			m_world->unload();
			_CrtDumpMemoryLeaks();
		}

		m_mainMenu->render(*m_window);
	}
	else {
		if (!m_world->initialized()) {
			m_world->load();
			m_gameManager->resumeGame();
		}

		m_world->render(*m_window);
	}

	m_uiManager->render(*m_window);

	m_window->display();
}