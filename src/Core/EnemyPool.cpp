#include "Core/EnemyPool.h"
#include "Core/AssetManager.h"
#include <Core/CollisionManager.h>
#include "Gameplay/Runner.h"
#include "Gameplay/Tank.h"

#include <algorithm>
#include <random>

EnemyPool* EnemyPool::s_instance{ nullptr };

Enemy* EnemyPool::getEnemy(sf::Vector2f position, Player* target) {
    for (auto* enemy : m_enemies) {
        if (!enemy->isDead()) continue;

        enemy->resetEnemy(position);
        m_activeEnemies.push_back(enemy);
        return enemy;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist(0, 2);
    int num = dist(gen);

    Enemy* enemy = parseEnemy(num);
    sf::Texture* texture = parseTexture(num);
    enemy->init(position, texture, target);

    m_enemies.push_back(enemy);
    m_activeEnemies.push_back(enemy);
    return enemy;
}

void EnemyPool::unloadEnemies() {

    delete s_instance;
}

void EnemyPool::update(float delta)
{
    m_activeEnemies.erase(std::remove_if(m_activeEnemies.begin(), m_activeEnemies.end(), [](Enemy* enemy) {return enemy->isDead();}), m_activeEnemies.end());

    for (auto* enemy : m_activeEnemies) {
        enemy->update(delta);
    }
}

void EnemyPool::render(sf::RenderWindow& window)
{
    for (auto* enemy : m_enemies) {
        if (enemy->isDead()) continue;

        enemy->render(window);
    }
}

Enemy* EnemyPool::parseEnemy(int num)
{
    Enemy* enemy{ nullptr };

    switch (num)
    {
    case 0:
        enemy = new Runner();
        break;
    case 1:
        enemy = new Shooter();
        break;
    case 2:
        enemy = new Tank();
        break;
    default:
        break;
    }

    return enemy;
}

sf::Texture* EnemyPool::parseTexture(int num)
{
    sf::Texture* tex{ nullptr };
    
    switch (num) 
    {
    case 0:
        tex = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/robot1_hold.png");
        break;
    case 1:
        tex = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/robot1_gun.png");
        break;
    case 2:
        tex = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/zombie1_reload.png");
        break;
    default:
        break;
    }

    return tex;
}
