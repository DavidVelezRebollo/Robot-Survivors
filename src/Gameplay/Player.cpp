#include "Core/AssetManager.h"
#include "Core/WeaponManager.h"
#include "Core/CollisionManager.h"

#include "Gameplay/Player.h"
#include "Gameplay/Projectile.h"
#include "Gameplay/Enemy.h"

#include "UI/UIManager.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Window/Event.hpp>

#include <math.h>
#include <iostream>

void Player::init(float delta) {
	sf::Texture* playerTexture = AssetManager::getInstance()->loadTexture("../Data/Images/hitman1_gun.png");
	m_sprite.setTexture(*playerTexture);
	m_sprite.setOrigin(playerTexture->getSize().x / 2.0f, playerTexture->getSize().y / 2.0f);

	m_speed.x *= delta;
	m_speed.y *= delta;

	m_currentHp = m_maxHp;
	m_isDead = false;

	setPosition(sf::Vector2f(UIManager::getInstance()->geWidth() * 0.5f, UIManager::getInstance()->getHeight() * 0.5f));
	CollisionManager::getInstance()->addCollider(this);
}

void Player::addExp(float amount)
{
	m_currentExp += amount;
	if (m_currentExp >= m_neededExp) levelUp();

	UIManager::getInstance()->getHUD()->addExperience(m_currentExp, m_neededExp);
}

void Player::onCollision(GameObject* collision)
{
	Projectile* bullet = dynamic_cast<Projectile*>(collision);

	if (bullet == nullptr) {
		takeDamage(dynamic_cast<Enemy*>(collision)->getDamage());
		return;
	}

	if (!bullet->canHurtPlayer()) return;
	
	takeDamage(bullet->getDamage());
}

void Player::update(float delta) {
	if (m_deltaThreshold > 0) m_deltaThreshold -= delta;

	Player::calculateDirection();

	m_position.x += (m_direction.x * m_speed.x * delta);
	m_position.y += (m_direction.y * m_speed.y * delta);

	setPosition(m_position);

	Player::calculateLookDirection();

	if (shootCooldown > 0) {
		shootCooldown -= delta;
		if (shootCooldown <= 0) shootCooldown = 0;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

	Weapon* weapon = WeaponManager::getInstance()->getCurrentWeapon();
	if (!weapon->canShoot()) return;

	weapon->shoot(getPosition());
}

void Player::render(sf::RenderWindow& window) {
	if (m_isDead) return;

	m_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

	window.draw(m_sprite);
}

void Player::calculateDirection() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direction.x = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direction.x = 1.0f;
	}
	else
	{
		m_direction.x = .0f;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_direction.y = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_direction.y = 1.0f;
	}
	else
	{
		m_direction.y = .0f;
	}
}

void Player::calculateLookDirection() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f playerPos = getPosition();

	sf::Vector2f direction(static_cast<float>(mousePos.x) - playerPos.x, static_cast<float>(mousePos.y) - playerPos.y);
	float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.141519f;

	m_sprite.setRotation(angle);
}

void Player::levelUp()
{
	UIManager::getInstance()->getHUD()->onLevelUp();

	m_level++;
	m_neededExp = 100 * pow(m_level, m_growthFactor);
	m_currentExp = 0.f;
}

void Player::takeDamage(float amount)
{
	if (m_deltaThreshold > 0) return;

	m_currentHp -= amount;
	SoundManager::getInstance()->onPlayerDamage();
	m_deltaThreshold = m_damageThreshold;

	UIManager::getInstance()->getHUD()->onHpChange(m_currentHp / m_maxHp);
	if (m_currentHp <= 0) {
		die();
	}
}

void Player::die()
{
	m_isDead = true;
	SoundManager::getInstance()->onPlayerDie();
	UIManager::getInstance()->getHUD()->onDie();
}
