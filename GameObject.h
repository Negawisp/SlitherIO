#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GfxManager.h"
#include "CollideLayer.h"
#include <vector>
#include <set>

class GameObject
{
private:
	static int _game_objects_count;


protected:
	int _id;
	CollideLayer _collide_layer;
	double _x;
	double _y;
	double _r;

public:
	static std::set<GameObject*> game_objects;
	static void delete_all_game_objects(); // TO BE CALLED AT THE VERY VERY END!!!

	bool _active;

	GameObject(bool active, CollideLayer collide_layer);
	~GameObject();

	int get_id();
	double get_x();
	double get_y();
	double get_r();
	CollideLayer get_collide_layer();

	virtual void draw()=0;
	virtual void collide(GameObject* other)=0;
	virtual void on_act(float dt)=0;
};

#endif // GAME_OBJECT_H