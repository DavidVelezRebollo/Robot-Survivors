#include "Gameplay/Weapon.h"

void Weapon::update(float delta)
{
	if (m_deltaShoot <= 0) return;

	m_deltaShoot -= delta;
}
