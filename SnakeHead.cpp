#include "SnakeHead.h"
#include "Snake.h"

void SnakeHead::turn(double angle)
{
	double new_x_dir = + _x_dir * cos(angle) + _y_dir * sin(angle);
	double new_y_dir = - _x_dir * sin(angle) + _y_dir * cos(angle);
	_x_dir = new_x_dir;
	_y_dir = new_y_dir;
}

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
