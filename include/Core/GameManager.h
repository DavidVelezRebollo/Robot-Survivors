#pragma once

#include <cmath>

class GameManager {
public:

	~GameManager() {
		s_instance = nullptr;
	}

	static GameManager* getInstance() {
		if (s_instance == nullptr) {
			s_instance = new GameManager();
		}

		return s_instance;
	}

	bool gamePaused() { return m_gamePaused; }
	void pauseGame() { m_gamePaused = true; }
	void resumeGame() { m_gamePaused = false; }

	int getTime() const { return std::floor(m_time / 1000.f); }
	int getEnemiesDefeated() const { return m_defeatedEnemies; }

	void defeatEnemy() { m_defeatedEnemies++; }
	void reset() { 
		m_time = 0.f; 
		m_defeatedEnemies = 0.f;
	}
	float calculateFinalScore() const;

	void update(float delta);
private:

	bool m_gamePaused{ true };
	float m_time{ 0.f };
	int m_defeatedEnemies{ 0 };
	static GameManager* s_instance;
};