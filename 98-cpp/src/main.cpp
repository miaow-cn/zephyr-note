#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <iostream>
#include <00_ref.hpp>
#include <01_class.hpp>

LOG_MODULE_REGISTER(98_cpp, LOG_LEVEL_INF);


int main()
{
    LOG_INF("Starting C++ examples...");
    ref_entry();
    class_entry();
    return 0;
}
