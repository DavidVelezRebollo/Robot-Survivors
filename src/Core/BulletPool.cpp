#include "Core/BulletPool.h"
#include "Core/AssetManager.h"
#include "Core/WeaponManager.h"

#include "Gameplay/Projectile.h"

#include <iostream>

BulletPool* BulletPool::m_instance{ nullptr };

Projectile* BulletPool::getBullet(char* texture, sf::Vector2f position, sf::Vector2f direction, float damage, bool canHurtPlayer, bool canPierce) {
	for (auto* bullet : m_bullets) {
		if (!bullet->isActive()) 
		{
			bullet->updateTexture(AssetManager::getInstance()->loadTexture(texture));
			bullet->setPosition(position);
			bullet->setDirection(direction);
			bullet->setPierce(canPierce);
			bullet->setCanHurtPlayer(canHurtPlayer);
			bullet->activate();
			return bullet;
		}
	}

	Projectile* bullet = new Projectile();
	m_bullets.push_back(bullet);
	m_bullets.back()->init(AssetManager::getInstance()->loadTexture(texture), position, direction, damage, canHurtPlayer, canPierce);

	return m_bullets.back();
}

void BulletPool::render(sf::RenderWindow& window) {
	for (auto* bullet : m_bullets) {
		if (!bullet->isActive()) continue;

		bullet->render(window);
	}
}

void BulletPool::update(float delta) {
	for (auto* bullet : m_bullets)
	{
		if (!bullet->isActive()) continue;

		if (bullet->isOutOfBounds()) {
			bullet->deactivate();
			continue;
		}

		bullet->update(delta);
	}
}