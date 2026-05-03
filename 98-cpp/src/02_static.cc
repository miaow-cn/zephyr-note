#include "02_static.h"
#include <zephyr/linker/section_tags.h>
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(static, LOG_LEVEL_INF);

namespace _02_static
{

class Entity
{
    static int x_, y_;

public:
    static void DoStatic()
    {
        x_++;
        y_--;
        std::cout << "Static method called " << x_ << ", " << y_ << std::endl;
    }

    void DoNonStatic()
    {
        x_++;
        y_--;
        std::cout << "Non-static method called " << x_ << ", " << y_ << std::endl;
    }
};

int Entity::x_ = 1;
int Entity::y_ = 1;

int Entry()
{
    LOG_INF("Starting Static example...");

    Entity entity, entity1;
    Entity::DoStatic();
    entity.DoNonStatic();
    entity1.DoNonStatic();

    std::cout << std::endl;
    return 0;
}

}