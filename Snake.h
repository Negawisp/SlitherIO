#ifndef SNAKE_H
#define SNAKE_H


#include "GameObject.h"
#include "SnakeSegment.h"
#include "SnakeHead.h"
#include <vector>

class Snake :
    public GameObject
{
private:
	uint32_t _color;
	bool _accelerates;

	SnakeHead* _head;
    std::vector<SnakeSegment*> _snake_segments;

public:
#define SNAKE_MINIMUM_LENGTH 10
#define INITIAL_R            50.0
#define L_BETWEEN_SEGMENTS   50.0
#define	V_STANDARD           50.0  / 1.0
#define V_ACCELERATED        100.0 / 1.0
#define TURNING_SPEED        M_PI / 1.0

	void decrease();
	void grow();

	void initialize_static_fields();

    Snake(bool active, int n_segments, double head_x, double head_y, uint32_t color);
	~Snake();

	void turn_left(float dt);
	void turn_right(float dt);
	void turn_to_point(double x_to, double y_to, float dt);
	void accelerate();

	void draw() override;
	void collide(GameObject* other) override;
	void on_act(float dt) override;
};

#endif // SNAKE_H