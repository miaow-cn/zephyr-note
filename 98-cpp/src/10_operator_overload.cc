#include "10_operator_overload.h"
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(operator_overload, LOG_LEVEL_INF);

namespace _10_operator_overload
{

struct Vector2 {
	float x, y;
	Vector2(float x, float y) : x(x), y(y)
	{
	}

	Vector2 operator*(const Vector2 &other) const
	{
		return Vector2(x * other.x, y * other.y);
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec)
	{
		os << "Vector2(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	Vector2 operator+(const Vector2 &other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 &operator+=(const Vector2 &other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	bool operator==(const Vector2 &other) const
	{
		return x == other.x && y == other.y;
	}

        bool operator!=(const Vector2 &other) const
	{
		return !(*this == other);
	}
};

int Entry()
{
	LOG_INF("Starting Operator Overload template...");

	Vector2 position(4.0f, 4);
	Vector2 speed(0.5f, 1.5f);
	Vector2 powerup(1.1f, 1.1f);

	Vector2 result = position + speed * powerup;
	std::cout << result << std::endl;

	std::cout << std::endl;
	return 0;
}

} // namespace _10_operator_overload
