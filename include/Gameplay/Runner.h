#pragma once

#include <Gameplay/Enemy.h>

class Runner : public Enemy {
public:

	void enemyBehaviour(float delta) override;
protected:
	void chaseTarget(float delta);
	void initStats() override;
};