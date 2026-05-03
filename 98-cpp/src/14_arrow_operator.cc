#include "14_arrow_operator.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(arrow_operator, LOG_LEVEL_INF);

using String = std::string;

namespace _14_arrow_operator
{

class Entity
{
public:
	int x_;
	int y_;

	Entity() : x_(0), y_(0)
	{
	}

	void Print() const
	{
		std::cout << "Entity(" << x_ << ")" << std::endl;
	}
};

class ScopedPtr
{
	using SourceLocation = std::source_location;
public:
	Entity *ptr_;

	explicit ScopedPtr(Entity *ptr) : ptr_(ptr)
	{
	}

	~ScopedPtr()
	{
		delete ptr_;
	}

	// Overload the arrow operator to return the pointer to Entity
	Entity *operator->()
	{
		std::cout << SourceLocation::current().function_name() << std::endl;
		return ptr_;
	}

	// Overload the arrow operator for const objects
	const Entity *operator->() const
	{
		std::cout << SourceLocation::current().function_name() << std::endl;
		return ptr_;
	}
};

int Entry()
{
	LOG_INF("Starting Arrow Operator example...");

	std::cout << "=== ScopedPtr entity ===" << std::endl;
	ScopedPtr entity(new Entity());
	// Print() as entity is a pointer to Entity
	entity->x_ = 2;
	entity->Print();

	std::cout << "=== const ScopedPtr entity ===" << std::endl;
	const ScopedPtr const_entity(new Entity());
	// Print() as const_entity is a pointer to const Entity
	const_entity->Print();

	std::cout << "=== offset of a member ===" << std::endl;
	int offset = (int)&(((Entity *)nullptr)->y_);
	std::cout << "Offset of x_: " << offset << std::endl;

	std::cout << std::endl;
	return 0;
}

} // namespace _14_arrow_operator
