#include <Gameplay/Projectile.h>
#include <SFML/Graphics/Texture.hpp>
#include <Gameplay/Player.h>
#include <Core/CollisionManager.h>
#include <Gameplay/Enemy.h>

#include <iostream>


void Projectile::init(const sf::Texture* texture, sf::Vector2f playerPos, sf::Vector2f direction, float damage, bool canHurtPlayer, bool canPierce)
{
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
	m_sprite.setScale(scale, scale);

	setPosition(playerPos);
	m_damage = damage;

	m_direction = direction;
	m_isActive = true;

	m_canHurtPlayer = canHurtPlayer;
	m_pierce = canPierce;

	CollisionManager::getInstance()->addCollider(this);
}

void Projectile::onCollision(GameObject* collision)
{
	if (dynamic_cast<Projectile*>(collision)) return;

	Player* player = dynamic_cast<Player*>(collision);

	if (player != nullptr && m_canHurtPlayer) {
		deactivate();
		return;
	}

	Enemy* enemy = dynamic_cast<Enemy*>(collision);

	if (enemy != nullptr && !m_canHurtPlayer) {
		if (!m_pierce) deactivate();
	}

}

void Projectile::update(float delta) {
	if (!isActive()) return;

	sf::Vector2f velocity = m_speed * delta * m_direction;
	m_sprite.move(velocity);
	m_position = m_sprite.getPosition();
}

void Projectile::render(sf::RenderWindow& window) {
	m_renderWindowSize = window.getSize();

	window.draw(m_sprite);
}

bool Projectile::isOutOfBounds() const {
	sf::Vector2f pos = getPosition();
	return pos.x < 0 || pos.y < 0 || pos.x >= m_renderWindowSize.x || pos.y >= m_renderWindowSize.y;
}

void Projectile::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

void Projectile::activate() {
	m_isActive = true;
	m_sprite.setColor(sf::Color(255.0f, 255.0f, 255.f, 255.f));
	CollisionManager::getInstance()->addCollider(this);
}

void Projectile::deactivate() {
	m_isActive = false;
	m_sprite.setColor(sf::Color(255.0f, 255.0f, 255.f, 0.f));
	CollisionManager::getInstance()->removeCollider(this);
}