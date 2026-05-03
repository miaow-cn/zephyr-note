#include "11_this.h"
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(this_example, LOG_LEVEL_INF);

namespace _11_this
{

class Entity
{
public:
	int x_;
	int y_;
	Entity(int x, int y)
	{
		this->x_ = x;
		this->y_ = y;
	}

	int GetX() const
	{
		// in const member function, we must use const pointer to this
		const Entity *const e = this;
		return e->x_;
	}
};


int Entry()
{
	LOG_INF("Starting This example...");

	Entity entity(1, 2);
	std::cout << "Entity x: " << entity.GetX() << std::endl;

	std::cout << std::endl;
	return 0;
}

} // namespace _11_this
