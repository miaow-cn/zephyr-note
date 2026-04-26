#include "05_inherit.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(inherit, LOG_LEVEL_INF);

using String = std::string;
using SourceLocation = std::source_location;
namespace _05_inherit
{

class Entity
{

public:
	int x_, y_;

	Entity() : x_(0), y_(0)
	{
		std::cout << "size of Entity is " << sizeof(Entity) << std::endl;
	}

	void Print()
	{
		std::cout << "Entity: x=" << x_ << " y=" << y_ << std::endl;
	}
};

class Player: public Entity
{
public:
	String name_;

	Player() : name_("Bob")
	{
		std::cout << "size of Player is " << sizeof(Player) << std::endl;
	}

	void PrintName()
	{
		std::cout << "Player: name=" << name_ << " x=" << x_ << " y=" << y_ << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Inherit example...");
	Player player;
	player.Print();
	player.PrintName();
	return 0;
}

} // namespace _05_inherit
