#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>
#include <04_destructor.hpp>

LOG_MODULE_REGISTER(destructor, LOG_LEVEL_INF);

using String = std::string;
using sl = std::source_location;
namespace _04_destructor
{

class Entity
{

public:
	float m_x, m_y;

	Entity()
	{
		std::cout << "Constructor, " << sl::current().function_name() << std::endl;
	}

	Entity(float x, float y) : m_x(x), m_y(y)
	{
		std::cout << "Constructor, " << sl::current().function_name() << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed, " << sl::current().function_name() << std::endl;
	}
};

int entry()
{
	LOG_INF("Starting Destructor example...");
	Entity e0;
	Entity e1(1.0f, 2.0f);
	return 0;
}

} // namespace _04_destructor
