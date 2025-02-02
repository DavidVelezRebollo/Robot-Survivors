#include <Gameplay/Enemy.h>
#include <Gameplay/Player.h>
#include <Gameplay/Projectile.h>
#include <Core/CollisionManager.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

bool Enemy::init(sf::Vector2f position, sf::Texture* enemyTexture, Player* target)
{
	m_target = target;

	m_sprite.setTexture(*enemyTexture);
	m_sprite.setOrigin(enemyTexture->getSize().x / 2.0f, enemyTexture->getSize().y / 2.0f);
	setPosition(position);

	m_deltaThreshold = m_damageThreshold;
	initStats();
	m_currentHp = m_maxHp;

	CollisionManager::getInstance()->addCollider(this);
	return true;
}

bool Enemy::isDead()
{
	return m_currentHp <= 0;
}

void Enemy::resetEnemy(sf::Vector2f position)
{
	m_currentHp = m_maxHp;
	m_sprite.setColor(sf::Color(255.f, 255.f, 255.f, 255.f));
	setPosition(position);
}

void Enemy::takeDamage(float amount)
{
	if (m_deltaThreshold > 0) return;

	m_currentHp -= amount;
	if (m_currentHp <= 0) die();
}

void Enemy::onCollision(GameObject* collision)
{
	if (dynamic_cast<Player*>(collision) || dynamic_cast<Enemy*>(collision)) return;

	Projectile* bullet = dynamic_cast<Projectile*>(collision);
	if (bullet == nullptr) return;

	if (bullet->canHurtPlayer()) return;

	takeDamage(bullet->getDamage());
	if (bullet->pierce()) m_deltaThreshold = m_damageThreshold;
}

void Enemy::update(float deltaMilliseconds)
{
	if (isDead()) return;

	if (m_deltaThreshold > 0) {
		m_deltaThreshold -= deltaMilliseconds;
	}

	enemyBehaviour(deltaMilliseconds);
}

void Enemy::render(sf::RenderWindow& window)
{
	m_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

	window.draw(m_sprite);
}

void Enemy::die()
{
	setPosition({ -99.f, -99.f });
	m_sprite.setColor(sf::Color(255.f, 255.f, 255.f, 0.f ));
	m_target->addExp(m_experience);

	SoundManager::getInstance()->onEnemyDie();
	GameManager::getInstance()->defeatEnemy();
}
