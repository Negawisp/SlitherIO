#include "SnakeSegment.h"
#include "Constants.h"

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

double SnakeSegment::get_dir_x()
{
	return _x_dir;
}

double SnakeSegment::get_dir_y()
{
	return _y_dir;
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

	_d_to_prev_segment = distance_between(this, prev_segment);

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

void SnakeSegment::instantiate(bool active, SnakeSegment* prev_segment, Snake* owner, uint32_t color, double x, double y, double d_to_prev_segment)
{
	_active = active;
	_owner = owner;
	_prev_segment = prev_segment;
	_color = color;

	_x   = x;
	_y   = y;
	_r   = prev_segment->_r;
	_v   = prev_segment->_v;
	_v_x = prev_segment->_v_x;
	_v_y = prev_segment->_v_y;
	_a   = 0;
	_a_x = 0;
	_a_y = 0;

	_x_dir = _v_x / _v;
	_y_dir = _v_y / _v;

	_d_to_prev_segment = d_to_prev_segment;
}

void SnakeSegment::return_to_pool()
{
	_owner = nullptr;
	_prev_segment = nullptr;
	_color = 0;

	_d_to_prev_segment = 0;
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

void SnakeSegment::turn(double angle)
{
	double new_x_dir = +_x_dir * cos(angle) + _y_dir * sin(angle);
	double new_y_dir = -_x_dir * sin(angle) + _y_dir * cos(angle);
	_x_dir = new_x_dir;
	_y_dir = new_y_dir;
}

void SnakeSegment::move(float dt)
{
	_x += _v_x * (double)dt;
	_y += _v_y * (double)dt;

	while (_x > GAME_FIELD_WIDTH)  { _x -= GAME_FIELD_WIDTH; }
	while (_x < 0)                 { _x += GAME_FIELD_WIDTH; }
	while (_y > GAME_FIELD_HEIGHT) { _y -= GAME_FIELD_HEIGHT; }
	while (_y < 0)                 { _y += GAME_FIELD_HEIGHT; }
}

void SnakeSegment::turn_to_point(double x_to, double y_to, float dt)
{
	double x_new_dir = x_to - _x;
	double y_new_dir = y_to - _y;
	double dot = _x_dir * x_new_dir + _y_dir * y_new_dir;
	double det = _x_dir * y_new_dir - _y_dir * x_new_dir;
	double angle = -atan2(det, dot);

	double max_angle = _turning_speed * (double)dt;

	if (angle > 0 &&
		angle > max_angle) {
		angle = max_angle;
	}

	if (angle < 0 &&
		angle < -max_angle) {
		angle = -max_angle;
	}

	turn(angle);
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
	double x_dir_seamless = x_dir + ((x_dir < 0) ? GAME_FIELD_WIDTH  : -GAME_FIELD_WIDTH);
	double y_dir = y_prev - _y;
	double y_dir_seamless = y_dir + ((y_dir < 0) ? GAME_FIELD_HEIGHT : -GAME_FIELD_HEIGHT);

	if (abs(x_dir) > abs(x_dir_seamless)) { x_dir = x_dir_seamless; }
	if (abs(y_dir) > abs(y_dir_seamless)) { y_dir = y_dir_seamless; }
	
	double dir_length = sqrt(x_dir * x_dir + y_dir * y_dir);
	x_dir = x_dir / dir_length;
	y_dir = y_dir / dir_length;

	double speed_modifier = pow(distance_between(this, _prev_segment) / _d_to_prev_segment, 3);
	if (speed_modifier > MAX_SPEED_MODIFIER) { speed_modifier = MAX_SPEED_MODIFIER; }
	if (speed_modifier < MIN_SPEED_MODIFIER) { speed_modifier = MIN_SPEED_MODIFIER; }

	_v_x = _v * x_dir * speed_modifier;
	_v_y = _v * y_dir * speed_modifier;
	_x_dir = _v_x / _v;
	_y_dir = _v_y / _v;

	move(dt);
}
