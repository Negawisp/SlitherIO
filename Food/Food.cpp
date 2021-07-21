#include "Food.h"
#include "../GfxManager.h"
#include "../Color.h"
#include "../CollideLayer.h"

std::vector<Food*> Food::_food_pool(2*FOOD_POOL_CAPACITY);
std::set<Food*> Food::_placed_food;

void Food::initialize_static_fields()
{
	int capacity = FOOD_POOL_CAPACITY;
	for (int i = 0; i < capacity; i++) {
		_food_pool.push_back(new Food());
	}
}

void Food::destroy_static_fields()
{
	int pool_size = (int)_food_pool.size();
	for (int i = 0; i < pool_size; i++) {
		delete _food_pool.back();
		_food_pool.pop_back();
	}

	for (std::set<Food*>::iterator i = _placed_food.begin(); i != _placed_food.end(); ++i) {
		delete (*i);
	}
	_placed_food.clear();
}

Food* Food::get_from_pool()
{
	Food* food = _food_pool.back();
	_food_pool.pop_back();
	return food;
}

void Food::spawn_food(double x, double y, double quality)
{
	Food* food = Food::get_from_pool();
	food->instantiate(x, y, quality);
}

void Food::draw_spawned_food()
{
	for (std::set<Food*>::iterator i = _placed_food.begin();
		i != _placed_food.end(); ++i) {
		Food* food = *i;
		food->draw();
	}
}

Food::Food() :
	GameObject(false, CollideLayer::FOOD)
{
	_quality = FOOD_MIN_QUALITY;
	_x = 0;
	_y = 0;
}


void Food::instantiate(double x, double y, double quality)
{
	_x = x;
	_y = y;
	_r = quality / 2;
	_quality = quality;
	_active = true;
	_placed_food.insert(this);
}

void Food::return_to_pool()
{
	_active = false;
	_placed_food.erase(this);
	_food_pool.push_back(this);
}

void Food::draw()
{
	GfxManager::drawCircle((int)_x, (int)_y, (int)_r, Color::GREEN);
}

void Food::collide(GameObject* other)
{
	if (CollideLayer::SNAKE_HEAD == other->get_collide_layer()) {
		return_to_pool();
	}
}

void Food::on_act(float dt)
{
	return;
}
