#pragma once

#include <Gameplay/GameObject.h>
#include <vector>
#include <iostream>

class CollisionManager {
	public:
		~CollisionManager() {
			m_colliders.clear();
			s_instance = nullptr;
		}

		static CollisionManager* getInstance() {
			if (s_instance == nullptr) {
				s_instance = new CollisionManager();
			}

			return s_instance;
		}

		void addCollider(GameObject* gameObject) { m_colliders.push_back(gameObject); }
		void removeCollider(GameObject* gameObject) { m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), gameObject), m_colliders.end()); }

		void update(float delta);
	private:
		static CollisionManager* s_instance;
		std::vector<GameObject*> m_colliders;
};