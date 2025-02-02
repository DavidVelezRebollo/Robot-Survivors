#include <Core/CollisionManager.h>
#include <iostream>

CollisionManager* CollisionManager::s_instance{ nullptr };

void CollisionManager::update(float delta)
{
	if (m_colliders.empty()) return;

	for (size_t i = 0; i < m_colliders.size(); ++i) {
		if (!m_colliders[i]) continue;

		for (size_t j = m_colliders.size() - 1; j > i; --j) {
			if (!m_colliders[j]) continue;

			if (m_colliders[i]->getBounds().intersects(m_colliders[j]->getBounds())) {

				m_colliders[i]->onCollision(m_colliders[j]);
				m_colliders[j]->onCollision(m_colliders[i]);
			}

			if (j >= m_colliders.size() || i >= m_colliders.size()) break;
		}
	}
}
