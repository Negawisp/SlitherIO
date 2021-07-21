#include "SnakeSegment.h"

std::vector<SnakeSegment*> SnakeSegment::segments_pool(2*SEGMENTS_POOL_CAPACITY);

void SnakeSegment::initialize_static_fields()
{
	int capacity = SEGMENTS_POOL_CAPACITY;
	for (int i = 0; i < capacity; i++)
	{
		segments_pool.push_back(new SnakeSegment());
	}
}

void SnakeSegment::destroy_static_fields()
{
	int n = (int)segments_pool.size();
	for (int i = 0; i < n; i++)
	{
		delete segments_pool.back();
		segments_pool.pop_back();
	}
}

double SnakeSegment::set_v(double v)
{
	_v_x = _v_x * v / _v;
	_v_y = _v_y * v / _v;
	_v   = v;

	return _v;
}

double SnakeSegment::get_x()
{
	return _x;
}

double SnakeSegment::get_y()
{
	return _y;
}

Snake* SnakeSegment::set_owner(Snake* owner)
{
	_owner = owner;
	return _owner;
}

SnakeSegment::SnakeSegment() :
	GameObject(false, CollideLayer::SNAKE)
{
	_owner = nullptr;
	_prev_segment = nullptr;
	_color = 0;

	_r   = 0;
	_x   = 0;
	_y   = 0;
	_v   = 0;
	_v_x = 0;
	_v_y = 0;
	_a   = 0;
	_a_x = 0;
	_a_y = 0;
}

SnakeSegment::SnakeSegment(bool active, SnakeSegment* prev_segment, uint32_t color) :
	GameObject(active, CollideLayer::SNAKE)
{
	_r   = prev_segment->_r;
	_x   = prev_segment->_x;
	_y   = prev_segment->_y;
	_v   = prev_segment->_v;
	_v_x = 0;
	_v_y = 0;
	_a   = 0;
	_a_x = 0;
	_a_y = 0;

	_owner = nullptr;
	_prev_segment = prev_segment;
	_color = color;
}

SnakeSegment* SnakeSegment::get_from_pool()
{
	SnakeSegment* back = segments_pool.back();
	segments_pool.pop_back();
	return back;
}

void SnakeSegment::instantiate(bool active, SnakeSegment* prev_segment, Snake* owner, uint32_t color, double x, double y)
{
	_active = active;
	_owner = owner;
	_prev_segment = prev_segment;
	_color = color;

	_x = x;
	_y = y;
	_r = prev_segment->_r;
	_v = prev_segment->_v;
	_v_x = 0;
	_v_y = 0;
	_a = 0;
	_a_x = 0;
	_a_y = 0;
}

void SnakeSegment::return_to_pool()
{
	_owner = nullptr;
	_prev_segment = nullptr;
	_color = 0;

	_r = 0;
	_x = 0;
	_y = 0;
	_v = 0;
	_v_x = 0;
	_v_y = 0;
	_a = 0;
	_a_x = 0;
	_a_y = 0;

	segments_pool.push_back(this);
}


void SnakeSegment::move(float dt)
{
	_x += _v_x * (double)dt;
	_y += _v_y * (double)dt;
}

void SnakeSegment::draw()
{
	GfxManager::drawCircle((int)_x, (int)_y, (int)_r, _color);
}

void SnakeSegment::collide(GameObject* other)
{
	return;
}


void SnakeSegment::on_act(float dt)
{
	if (!_active) { return; }

	double x_prev = _prev_segment->_x;
	double y_prev = _prev_segment->_y;
	
	double x_dir = x_prev - _x;
	double y_dir = y_prev - _y;
	double dir_length = sqrt(x_dir * x_dir + y_dir * y_dir);
	x_dir = x_dir / dir_length;
	y_dir = y_dir / dir_length;

	_v_x = _v * x_dir;
	_v_y = _v * y_dir;

	move(dt);
}
