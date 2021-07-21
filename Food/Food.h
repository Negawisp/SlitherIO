#ifndef FOOD_H
#define FOOD_H

#include "../GameObject.h"
#include <vector>
#include <set>

class Food :
    public GameObject
{
private:
    static std::vector<Food*> _food_pool;
    static std::set<Food*> _placed_food;
    double _quality;

public:
#define FOOD_POOL_CAPACITY  1024
#define FOOD_MAX_QUALITY    50.0
#define FOOD_MIN_QUALITY    10.0
#define FOOD_SPAWN_COOLDOWN 3


    static void initialize_static_fields();
    static void destroy_static_fields();
    static Food* get_from_pool();

    static void spawn_food(double x, double y, double quality);
    static void draw_spawned_food();

    Food();

    void instantiate(double x, double y, double quality);
    void return_to_pool();

    void draw() override;
    void collide(GameObject* other) override;
    void on_act(float dt) override;
};

#endif // FOOD_H