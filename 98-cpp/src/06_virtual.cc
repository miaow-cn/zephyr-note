#include "06_virtual.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(virtual, LOG_LEVEL_INF);

using String = std::string;
using SourceLocation = std::source_location;
namespace _06_virtual
{

class Entity
{

public:
	int x_, y_;

	Entity() : x_(0), y_(0)
	{
	}

	// This class is used polymorphically (it has virtual methods).
	// The destructor must be virtual so deleting through Entity* calls
	// the full derived destructor chain and avoids undefined behavior.
	virtual ~Entity() = default;

	virtual void Print()
	{
		std::cout << "Entity: x=" << x_ << " y=" << y_ << std::endl;
	}

	void PrintName()
	{
		std::cout << "Entity: No name, x=" << x_ << " y=" << y_ << std::endl;
	}
};

class Player: public Entity
{
public:
	String name_;

	Player() : name_("Bob")
	{
	}

	void Print() override
	{
		std::cout << "Player: x=" << x_ << " y=" << y_ << std::endl;
	}

	void PrintName()
	{
		std::cout << "Player: name=" << name_ << " x=" << x_ << " y=" << y_ << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Virtual example...");
	Player *player = new Player();
	Entity *entity = player;
	entity->Print();     // Print is virtual, so it will call Player::Print()
	entity->PrintName(); // PrintName is not virtual, so it will call Entity::PrintName()

	delete player;
	return 0;
}

} // namespace _06_virtual
