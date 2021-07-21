#include "CollidingManager.h"
#include <math.h>
#include "../GameObject.h"

void CollidingManager::collide(GameObject* go1, GameObject* go2)
{
	if (go1->_active && go2->_active) {
		double r = GameObject::distance_between(go1, go2);
		if (r < go1->get_r() + go2->get_r()) {
			go1->collide(go2);
			go2->collide(go1);
		}
	}
}

void CollidingManager::collide_all()
{
	for (std::set<GameObject*>::iterator i = GameObject::game_objects.begin();
		 i != GameObject::game_objects.end(); ++i)
	{
		GameObject* go1 = *i;
		if (!(go1->_active)) { continue; }

		for (std::set<GameObject*>::iterator j = std::next(i, 1);
			j != GameObject::game_objects.end(); ++j)
		{
			collide(*i, *j);
		}
	}
}
