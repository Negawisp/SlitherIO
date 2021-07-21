#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "GameObject.h"
#include <algorithm>

int GameObject::_game_objects_count = 0;
std::set<GameObject*> GameObject::game_objects;

GameObject::GameObject(bool active, CollideLayer collide_layer) {
	_x = 0;
	_y = 0;
	_r = 0;
	_id = ++_game_objects_count;
	_active = active;
	_collide_layer = collide_layer;
	game_objects.insert(this);
}

void GameObject::delete_all_game_objects()
{
	
	for (std::set<GameObject*>::iterator i = game_objects.begin(); i != game_objects.end(); i++) {
		delete (*i);
	}
	game_objects.clear();
}

int GameObject::get_id()
{
	return _id;
}

CollideLayer GameObject::get_collide_layer()
{
    return _collide_layer;
}

double GameObject::distance_between(const GameObject* a, const GameObject* b)
{
	return sqrt(pow((a->_x - b->_x), 2) + pow((a->_y - b->_y), 2));
}

GameObject::~GameObject()
{
	game_objects.erase(this);
}

double GameObject::get_x()
{
	return _x;
}

double GameObject::get_y()
{
	return _y;
}

double GameObject::get_r()
{
	return _r;
}

#endif // GAME_OBJECT