#include <Core/GameManager.h>

GameManager* GameManager::s_instance{ nullptr };

float GameManager::calculateFinalScore() const
{
	float timeScore = m_time / 1000.f;
	float enemiesScore = m_defeatedEnemies;

	return timeScore + enemiesScore;
}

void GameManager::update(float delta)
{
	if (m_gamePaused) return;

	m_time += delta;
}
