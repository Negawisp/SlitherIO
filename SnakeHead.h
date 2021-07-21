#ifndef SNAKE_HEAD_H
#define SNAKE_HEAD_H

#include "SnakeSegment.h"

class SnakeHead :
    public SnakeSegment
{
private:
    double _x_dir;
    double _y_dir;
    double _turning_speed;
    
    void turn(double angle);
public:
    SnakeHead(bool active, uint32_t color, double turning_speed, double x, double y, double v_x, double v_y, double r);
    void turn_left(float dt);
    void turn_right(float dt);
    void turn_to_point(double x_to, double y_to, float dt);

    void collide(GameObject* other) override;
    void on_act(float dt) override;
};


#endif // !SNAKE_HEAD_H