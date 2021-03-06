#ifndef SNAKE_SEGMENT_H
#define SNAKE_SEGMENT_H

#include "GameObject.h"
#include "Color.h"

class Snake;

class SnakeSegment :
    public GameObject
{
private:
    static const int SEGMENTS_POOL_CAPACITY = 1024;
    static std::vector<SnakeSegment*> segments_pool;

protected:
    double _v_x, _v_y, _v;
    double _a_x, _a_y, _a;
    double _d_to_prev_segment;
    uint32_t _color;
    Snake* _owner;
    SnakeSegment* _prev_segment;

    double _x_dir;
    double _y_dir;
    double _turning_speed;

    void turn(double angle);
    void move(float dt);
    void turn_to_point(double x_to, double y_to, float dt);

public:
#define MAX_SPEED_MODIFIER 4.5
#define MIN_SPEED_MODIFIER 0.1

    static void initialize_static_fields();
    static void destroy_static_fields();

    double set_v(double v);
    double get_x();
    double get_y();
    double get_dir_x();
    double get_dir_y();
    Snake* set_owner(Snake* owner);

    SnakeSegment();
    SnakeSegment(bool active, SnakeSegment* prev_segment, uint32_t color);

    static SnakeSegment* get_from_pool();
    void instantiate(bool active, SnakeSegment* prev_segment, Snake* owner, uint32_t color, double x, double y, double d_to_prev_segment);
    void return_to_pool();

    void draw() override;
    void collide(GameObject* other) override;
    void on_act(float dt) override;
};


#endif // SNAKE_SEGMENT_H