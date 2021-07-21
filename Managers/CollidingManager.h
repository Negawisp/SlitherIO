#ifndef COLLIDING_MANAGER_H
#define COLLIDING_MANAGER_H

#include "../GameObject.h"

class CollidingManager {
private:
public:
	static void collide(GameObject* go1, GameObject* go2);
	static void collide_all();
};

#endif // COLLIDING_MANAGER_H
