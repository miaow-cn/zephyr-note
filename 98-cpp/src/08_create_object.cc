#include "08_create_object.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <new>

LOG_MODULE_REGISTER(create_object, LOG_LEVEL_INF);

namespace _08_create_object
{

class Person
{
private:
	const char *name_;
	int age_;

public:
	Person() : name_("Unknown"), age_(30)
	{
	}

	Person(const char *name, int age) : name_(name), age_(age)
	{
	}

	~Person() = default;

	void Print() const
	{
		std::cout << "Person   : " << name_ << " (" << age_ << ")" << std::endl;
	}
};

int Entry()
{
	LOG_INF("Starting Create Object example...");

	// Default initialization
	Person mike;
	mike.Print();

	// Direct initialization: T obj(args)
	Person alice("Alice", 18);
	alice.Print();

	// Copy initialization: T obj = T(args)
	Person alice2 = Person("Alice2", 18);
	alice2.Print();

	// Direct-list initialization: T obj{args}
	Person lily{"Lily", 19};
	lily.Print();

	// Copy-list initialization: T obj = {args}
	Person rose = {"Rose", 20};
	rose.Print();

	// Value/list initialization with default constructor: T obj{}
	Person default_by_brace{};
	default_by_brace.Print();

	// Copy initialization from existing object: T obj = other
	Person rose_copy = rose;
	rose_copy.Print();

	// Temporary object (anonymous object)
	Person("Temp", 99).Print();

	// Array with list initialization: T obj[] = {args}
	Person group[] = {
		{"GroupA", 21},
		{"GroupB", 22},
	};
	for (const Person &item : group) {
		item.Print();
	}

	// Heap object with direct initialization: T *obj = new T(args)
	Person *bob = new Person("Bob", 23);
	bob->Print();
	delete bob;

	// Heap object with list initialization: T *obj = new T{args}
	Person *jack = new Person{"Jack", 24};
	jack->Print();
	delete jack;

	// Dynamic array allocation with list initialization: new T[n]{...}
	Person *team = new Person[2]{{"TeamA", 30}, {"TeamB", 31}};
	team[0].Print();
	team[1].Print();
	delete[] team;

	// Placement new: construct object in raw pre-allocated memory.
	void *raw = ::operator new(sizeof(Person));
	Person *charlie = new(raw) Person("Charlie", 25);
	charlie->Print();
	charlie->~Person();
	::operator delete(raw);

	return 0;
}

} // namespace _08_create_object
