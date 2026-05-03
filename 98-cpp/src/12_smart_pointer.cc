#include "12_smart_pointer.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <memory>

LOG_MODULE_REGISTER(smart_pointer_example, LOG_LEVEL_INF);

namespace _12_smart_pointer
{

class Entity
{

public:
	int x_;
	explicit Entity(int x) : x_(x)
	{
		std::cout << "Entity(" << x_ << ") created" << std::endl;
	}

	~Entity()
	{
		std::cout << "Entity(" << x_ << ") destroyed" << std::endl;
	}

	void Print()
	{
		std::cout << "Entity(" << x_ << ")" << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Smart Pointer example...");

	{
		// unique_ptr is a smart pointer that owns an object exclusively.
		// It automatically deletes the object when it goes out of scope.
		std::cout << "=== Using unique_ptr ===" << std::endl;
		std::unique_ptr<Entity> entity = std::make_unique<Entity>(1);
		entity->Print();
		// we cannot copy unique_ptr, but we can move it
		// std::unique_ptr<Entity> entity2 = entity;
		std::unique_ptr<Entity> entity2 = std::move(entity);
	}

	{
		// shared_ptr allows multiple ownership.
		// It automatically deletes the object when the last shared_ptr owning destroyed.
		std::cout << "=== Using shared_ptr ===" << std::endl;
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(2);
		entity->Print();
		std::shared_ptr<Entity> entity2 = entity; // shared ownership
		std::cout << "Entity use count: " << entity.use_count() << std::endl;
	}

	{
		// weak_ptr is a smart pointer that holds a non-owning reference to an object
		// managed by shared_ptr. It allows you to check if the object still exists without
		// preventing its destruction.
		std::cout << "=== Using weak_ptr ===" << std::endl;
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(3);
		std::weak_ptr<Entity> weak_entity = entity; // non-owning reference
		std::cout << "Entity use count: " << entity.use_count() << std::endl;
		// check if the object still exists
		if (auto shared_entity = weak_entity.lock()) {
			shared_entity->Print();
		} else {
			std::cout << "Entity has been destroyed" << std::endl;
		}
	}

	std::cout << std::endl;
	return 0;
}

} // namespace _12_smart_pointer
