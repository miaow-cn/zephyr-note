#include <zephyr/linker/section_tags.h>
#include <zephyr/logging/log.h>
#include <iostream>
#include <02_static.hpp>

LOG_MODULE_REGISTER(static, LOG_LEVEL_INF);

namespace _02_static
{

class Entity
{
    static int x, y;

public:
    static void do_static()
    {
        x++;
        y--;
        std::cout << "Static method called " << x << ", " << y << std::endl;
    }

    void do_non_static()
    {
        x++;
        y--;
        std::cout << "Non-static method called " << x << ", " << y << std::endl;
    }
};

int Entity::x = 1;
int Entity::y = 1;

int entry()
{
    LOG_INF("Starting Static example...");

    Entity e, e1;
    Entity::do_static();
    e.do_non_static();
    e1.do_non_static();

    return 0;
}

}