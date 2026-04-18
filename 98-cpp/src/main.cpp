#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <iostream>
#include <00_ref.hpp>

LOG_MODULE_REGISTER(98_cpp, LOG_LEVEL_INF);


int main()
{
    LOG_INF("Starting C++ examples...");
    ref_entry();
    return 0;
}
