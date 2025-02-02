#include "Core/SoundManager.h"
#include "SFML/Audio.hpp"

SoundManager* SoundManager::s_instance{ nullptr };

void SoundManager::init() 
{
	s_instance = this;

	m_musicBuffer = sf::SoundBuffer();
	m_musicBuffer.loadFromFile("../Data/Sounds/Music.wav");

	m_pistolBuffer = sf::SoundBuffer();
	m_pistolBuffer.loadFromFile("../Data/Sounds/Pistol.wav");

	m_raygunBuffer = sf::SoundBuffer();
	m_raygunBuffer.loadFromFile("../Data/Sounds/Raygun.wav");

	m_shootgunBuffer = sf::SoundBuffer();
	m_shootgunBuffer.loadFromFile("../Data/Sounds/Shotgun_Shoot.wav");

	m_bombBuffer = sf::SoundBuffer();
	m_bombBuffer.loadFromFile("../Data/Sounds/Explosion.wav");

	m_playerDamageBuffer = sf::SoundBuffer();
	m_playerDamageBuffer.loadFromFile("../Data/Sounds/Player_Hurt.ogg");

	m_playerDieBuffer = sf::SoundBuffer();
	m_playerDieBuffer.loadFromFile("../Data/Sounds/Lost.wav");

	m_enemyDieBuffer = sf::SoundBuffer();
	m_enemyDieBuffer.loadFromFile("../Data/Sounds/Enemy_Die.wav");
}

void SoundManager::playMusic() { playSound(m_musicBuffer, true); }

void SoundManager::pistolShoot() { playSound(m_pistolBuffer); }
void SoundManager::shootgunShoot() { playSound(m_shootgunBuffer); }
void SoundManager::raygunShoot() { playSound(m_raygunBuffer); }
void SoundManager::bombExplotion() { playSound(m_bombBuffer); }

void SoundManager::onPlayerDie() { playSound(m_playerDieBuffer); }
void SoundManager::onPlayerDamage() { playSound(m_playerDamageBuffer); }

void SoundManager::onEnemyDie() { playSound(m_enemyDieBuffer); }

void SoundManager::playSound(const sf::SoundBuffer& buffer, bool loop)
{
	clearSounds();

	sf::Sound* sound = new sf::Sound();
	m_sounds.emplace_back(sound);
	m_sounds.back()->setBuffer(buffer);
	m_sounds.back()->setLoop(loop);
	m_sounds.back()->setVolume(10);
	m_sounds.back()->play();
}

void SoundManager::clearSounds() {
	m_sounds.erase(std::remove_if(m_sounds.begin(), m_sounds.end(), [](sf::Sound* sound) {return sound->getStatus() == sf::Sound::Stopped;}), m_sounds.end());
}
