#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GfxManager.h"
#include "CollideLayer.h"
#include <vector>

class GameObject
{
private:
	static int _game_objects_count;
	CollideLayer _collide_layer;

protected:
	int _id;

public:
	bool _active;

	GameObject(bool active, CollideLayer collide_layer);

	int get_id();
	CollideLayer get_collide_layer();

	virtual void draw()=0;
	virtual void collide(GameObject* other)=0;
	virtual void on_act(float dt)=0;
};

#endif // GAME_OBJECT_H