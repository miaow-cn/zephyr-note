#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>
#include <03_constructor.hpp>

LOG_MODULE_REGISTER(constructor, LOG_LEVEL_INF);

using String = std::string;
using sl = std::source_location;
namespace _03_constructor
{

class Entity
{

public:
	float m_x, m_y;

	Entity() = delete;
	Entity(float x) : m_x(x)
	{
		String msg = std::format(": x={} y={}", m_x, m_y);
		std::cout << sl::current().function_name() << msg << std::endl;
	}

	Entity(float x, float y) : m_x(x), m_y(y)
	{
		String msg = std::format(": x={} y={}", m_x, m_y);
		std::cout << sl::current().function_name() << msg << std::endl;
	}
};

int entry()
{
	LOG_INF("Starting Constructor example...");
	Entity e0(1.0f);
	Entity e2(1.0f, 2.0f);
	return 0;
}

} // namespace _03_constructor
