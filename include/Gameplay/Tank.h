#pragma once

#include <Gameplay/Enemy.h>

class Tank : public Enemy {
public:

	void enemyBehaviour(float delta) override;

private:

	void chaseTarget(float delta);
	void initStats() override;
};