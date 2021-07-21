#ifndef PLAYER_SNAKE
#define PLAYER_SNAKE


#include "Snake.h"
class PlayerSnake :
    public Snake
{
public:
    PlayerSnake(bool active, int n_segments, double head_x, double head_y, uint32_t color, uint32_t head_color);
};


#endif // !PLAYER_SNAKE