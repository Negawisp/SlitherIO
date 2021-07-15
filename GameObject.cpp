#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "GameObject.h"
#include <algorithm>

int GameObject::_game_objects_count = 0;

GameObject::GameObject(bool active, CollideLayer collide_layer) {
	_id = ++_game_objects_count;
	_active = active;
	_collide_layer = collide_layer;
}

int GameObject::get_id()
{
	return _id;
}

CollideLayer GameObject::get_collide_layer()
{
    return _collide_layer;
}

#endif // GAME_OBJECT