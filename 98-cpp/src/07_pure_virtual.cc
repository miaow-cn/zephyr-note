#include "07_pure_virtual.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>
#include <source_location>

LOG_MODULE_REGISTER(pure_virtual, LOG_LEVEL_INF);

using String = std::string;

namespace _07_pure_virtual
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

	virtual void Print() = 0; // Pure virtual function, making Entity an abstract class

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
	LOG_INF("Starting Pure Virtual example...");

        // We can't create an instance of Entity because it is an abstract class
	Player *player = new Player();
	player->Print(); 
	player->PrintName();

	delete player;
	std::cout << std::endl;
	return 0;
}

} // namespace _07_pure_virtual