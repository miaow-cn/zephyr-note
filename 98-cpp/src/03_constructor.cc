#include "03_constructor.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(constructor, LOG_LEVEL_INF);

using String = std::string;
using SourceLocation = std::source_location;
namespace _03_constructor
{

class Entity
{

public:
	float x_, y_;

	Entity() = delete;
	Entity(float x) : x_(x)
	{
		String msg = std::format(": x={} y={}", x_, y_);
		std::cout << SourceLocation::current().function_name() << msg << std::endl;
	}

	Entity(float x, float y) : x_(x), y_(y)
	{
		String msg = std::format(": x={} y={}", x_, y_);
		std::cout << SourceLocation::current().function_name() << msg << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Constructor example...");
	Entity entity0(1.0f);
	Entity entity2(1.0f, 2.0f);
	return 0;
}

} // namespace _03_constructor
