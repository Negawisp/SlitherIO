#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include "Color.h"
#include "GfxManager.h"
#include <iostream>

#include "SnakeSegment.h"
#include "PlayerSnake.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

const int SNAKE_INITIAL_LENGTH = 10;
PlayerSnake* player_snake;

// initialize game data in this function
void initialize()
{
    SnakeSegment::initialize_static_fields();
    player_snake = new PlayerSnake(true, SNAKE_INITIAL_LENGTH, 500.0, 500.0, Color::RED);
    void clear_buffer();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (is_key_pressed(VK_ESCAPE)) {
        schedule_quit_game();
    }
    if (is_key_pressed(VK_LEFT)) {
        player_snake->turn_left(dt);
    }
    if (is_key_pressed(VK_RIGHT)) {
        player_snake->turn_right(dt);
    }
    if (is_key_pressed('A')) {
        player_snake->grow();
    }
    if (is_key_pressed('B') || is_mouse_button_pressed(1)) {
        player_snake->accelerate();
    }
    if (is_mouse_button_pressed(0)) {
        int x = get_cursor_x();
        int y = get_cursor_y();
        player_snake->turn_to_point(get_cursor_x(), get_cursor_y(), dt);
    }
    
    player_snake->on_act(dt);
}

int c = 0;
// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    clear_buffer();
    //GfxManager::drawCircle(200, 200, 99, Color::RED);
    player_snake->draw();
}

// free game data in this function
void finalize()
{
    delete player_snake;
    SnakeSegment::destroy_static_fields();
}
