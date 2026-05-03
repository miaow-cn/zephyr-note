#include "13_copy_constructor.h"
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(copy_constructor_example, LOG_LEVEL_INF);
using SourceLocation = std::source_location;

namespace _13_copy_constructor
{

struct Vector2 {
	float x;
	float y;
	Vector2(float x, float y) : x(x), y(y)
	{
	}

	Vector2(const Vector2 &other) : x(other.x), y(other.y)
	{
		std::cout << "Copy constructor called" << std::endl;
	}
};

void PrintVector(const Vector2 v)
{
	std::cout << v.y << std::endl;
}

int Entry()
{
	LOG_INF("Starting Copy Constructor example...");

	Vector2 v1{1.0f, 2.0f};
	Vector2 v2 = v1; // Copy constructor

	std::cout << "v1: (" << v1.x << ", " << v1.y << ")" << std::endl;
	std::cout << "v2: (" << v2.x << ", " << v2.y << ")" << std::endl;

	PrintVector(v2); // Copy constructor

	std::cout << std::endl;
	return 0;
}

} // namespace _13_copy_constructor
