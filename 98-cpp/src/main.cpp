#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <iostream>
#include <00_ref.hpp>
#include <01_class.hpp>
#include <02_static.hpp>
#include <03_constructor.hpp>
#include <04_destructor.hpp>

LOG_MODULE_REGISTER(98_cpp, LOG_LEVEL_INF);

int main()
{
	LOG_INF("Starting C++ examples...");
	ref_entry();
	_01_class::entry();
	_02_static::entry();
	_03_constructor::entry();
	_04_destructor::entry();

	return 0;
}
