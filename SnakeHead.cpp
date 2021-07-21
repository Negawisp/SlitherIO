#include "SnakeHead.h"
#include "Snake.h"

SnakeHead::SnakeHead(bool active, uint32_t color, double turning_speed, double x, double y, double v_x, double v_y, double r) :
	SnakeSegment()
{
	_active = active;
	_r = r;
	_x = x;
	_y = y;
	_v = sqrt(v_x * v_x + v_y * v_y);
	_v_x = v_x;
	_v_y = v_y;
	_x_dir = v_x / _v;
	_y_dir = v_y / _v;
	_turning_speed = abs(turning_speed);
	_color = color;
	_collide_layer = CollideLayer::SNAKE_HEAD;
}

void SnakeHead::turn_left(float dt)
{
	double turning_angle = + _turning_speed * dt;
	turn(turning_angle);
}

void SnakeHead::turn_right(float dt)
{
	double turning_angle = - _turning_speed * (double)dt;
	turn(turning_angle);
}

void SnakeHead::turn_to_point(double x_to, double y_to, float dt)
{
	__super::turn_to_point(x_to, y_to, dt);
}

void SnakeHead::collide(GameObject* other)
{
	if (CollideLayer::FOOD == other->get_collide_layer()) {
		// grow
		this->_owner->grow();
	}

	if (CollideLayer::SNAKE == other->get_collide_layer() &&
		other->get_id() != _id) {
		// die
	}
}

void SnakeHead::on_act(float dt)
{
	if (!_active) { return; }

	_v_x = _v * _x_dir;
	_v_y = _v * _y_dir;
	move(dt);
}
