#include "04_destructor.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(destructor, LOG_LEVEL_INF);

using String = std::string;
using SourceLocation = std::source_location;
namespace _04_destructor
{

class Entity
{

public:
	float x_, y_;

	Entity()
	{
		std::cout << "Constructor, " << SourceLocation::current().function_name() << std::endl;
	}

	Entity(float x, float y) : x_(x), y_(y)
	{
		std::cout << "Constructor, " << SourceLocation::current().function_name() << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed, " << SourceLocation::current().function_name() << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Destructor example...");
	Entity entity0;
	Entity entity1(1.0f, 2.0f);
	std::cout << std::endl;
	return 0;
}

} // namespace _04_destructor
