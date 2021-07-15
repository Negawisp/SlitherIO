#include "Snake.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>


Snake::Snake(bool active, int n_segments, double head_x, double head_y, uint32_t color) :
	GameObject(active, CollideLayer::NONE),
	_snake_segments()
{
	_head = new SnakeHead(true, this, color, TURNING_SPEED, head_x, head_y, V_STANDARD, 0, INITIAL_R);
	_color = color;

	// Make initial snake
	SnakeSegment* prev_segment = _head;
	for (int i = 0; i < n_segments; i++) {
		SnakeSegment* segment = SnakeSegment::get_from_pool();
		segment->instantiate(true, prev_segment, this, color, prev_segment->get_x() - L_BETWEEN_SEGMENTS, prev_segment->get_y());
		_snake_segments.push_back(segment);
		prev_segment = segment;
	}
}

void Snake::decrease()
{
	if (_snake_segments.size() <= SNAKE_MINIMUM_LENGTH) { return; }
	SnakeSegment* tail = _snake_segments.back();
	tail->return_to_pool();
	_snake_segments.pop_back();
}

void Snake::grow()
{
	SnakeSegment* tail = _snake_segments.back();
	double tail_x = tail->get_x();
	double tail_y = tail->get_y();

	SnakeSegment* segment = SnakeSegment::get_from_pool();
	segment->instantiate(true, tail, this, _color, tail_x - L_BETWEEN_SEGMENTS, tail_y);
	_snake_segments.push_back(segment);
}


void Snake::draw()
{
	// draw all segments starting from tail
	for (std::vector<SnakeSegment*>::reverse_iterator i = _snake_segments.rbegin();
		 i != _snake_segments.rend(); ++i)
	{
		if (nullptr == *i) { break; }

		SnakeSegment* segment = *i;
		segment->draw();
	}
	_head->draw();
}

void Snake::collide(GameObject* other)
{
	return;
}

void Snake::on_act(float dt)
{
	// controls and setting parameters on segments.
	// ACTs OF SEGMENTS WILL BE CALLED NOT FROM HERE BUT FROM GENERAL ACT CALLER!!
	double v = _accelerates ? V_ACCELERATED : V_STANDARD;
	_head->set_v(v);
	_head->on_act(dt);
	for (std::vector<SnakeSegment*>::iterator i = _snake_segments.begin();
		i != _snake_segments.end(); ++i)
	{
		SnakeSegment* segment = *i;
		segment->set_v(v);
		segment->on_act(dt);
	}
	_accelerates = false;
}

void Snake::turn_left(float dt)
{
	_head->turn_left(dt);
}

void Snake::turn_right(float dt)
{
	_head->turn_right(dt);
}

void Snake::turn_to_point(double x_to, double y_to, float dt)
{
	_head->turn_to_point(x_to, y_to, dt);
}

void Snake::accelerate()
{
	_accelerates = true;
}

Snake::~Snake()
{
	delete _head;
	int n = (int)_snake_segments.size();
	for (int i = 0; i < n; i++)
	{
		delete _snake_segments.back();
		_snake_segments.pop_back();
	}
}
