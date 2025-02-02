#pragma once

#include <SFML/Audio.hpp>
#include <vector>

class SoundManager {
public:

	~SoundManager() {
		for (sf::Sound* sound : m_sounds) {
			delete sound;
			sound = nullptr;
		}

		s_instance = nullptr;
	}

	static SoundManager* getInstance() {
		if (s_instance == nullptr) {
			s_instance = new SoundManager();
		}

		return s_instance;
	}

	void init();

	void playMusic();
	void pistolShoot();
	void shootgunShoot();
	void raygunShoot();
	void bombExplotion();

	void onPlayerDie();
	void onPlayerDamage();

	void onEnemyDie();

private:
	void playSound(const sf::SoundBuffer& buffer, bool loop = false);
	void clearSounds();

	static SoundManager* s_instance;

	sf::SoundBuffer m_musicBuffer;
	sf::SoundBuffer m_pistolBuffer;
	sf::SoundBuffer m_shootgunBuffer;
	sf::SoundBuffer m_raygunBuffer;
	sf::SoundBuffer m_bombBuffer;

	sf::SoundBuffer m_playerDieBuffer;
	sf::SoundBuffer m_playerDamageBuffer;

	sf::SoundBuffer m_enemyDieBuffer;

	std::vector<sf::Sound*> m_sounds;
};